
#include <atomic>

#include "../tbb/include/oneapi/tbb/detail/_namespace_injection.h"
#include "../tbb/include/oneapi/tbb/task_arena.h"

#include "../tbb/src/tbb/observer_proxy.h"
#include "../tbb/src/tbb/main.h"
#include "../tbb/src/tbb/thread_data.h"

#ifdef _WIN32
# define DLL_EXPORT __declspec(dllexport)
#else
# define DLL_EXPORT
#endif

namespace tbb {

namespace interface6 {
class task_scheduler_observer;
}

namespace internal {

class task_scheduler_observer_v3 {
   friend class tbb::detail::r1::observer_proxy;
   friend class tbb::detail::r1::observer_list;
   friend class interface6::task_scheduler_observer;
   
   //! Pointer to the proxy holding this observer.
   /** Observers are proxied by the scheduler to maintain persistent lists of them. **/
   tbb::detail::r1::observer_proxy* my_proxy;
   
   //! Counter preventing the observer from being destroyed while in use by the scheduler.
   /** Valid only when observation is on. **/
   std::atomic<intptr_t> my_busy_count;
   
public:
   //! Enable or disable observation
   /** For local observers the method can be used only when the current thread
    has the task scheduler initialized or is attached to an arena.
    Repeated calls with the same state are no-ops. **/
   void DLL_EXPORT __TBB_EXPORTED_METHOD observe( bool state=true );
   
   //! Returns true if observation is enabled, false otherwise.
   bool is_observing() const {return my_proxy!=NULL;}
   
   //! Construct observer with observation disabled.
   task_scheduler_observer_v3() : my_proxy(NULL) { my_busy_count.store(0); }
   
   //! Entry notification
   /** Invoked from inside observe(true) call and whenever a worker enters the arena
    this observer is associated with. If a thread is already in the arena when
    the observer is activated, the entry notification is called before it
    executes the first stolen task.
    Obsolete semantics. For global observers it is called by a thread before
    the first steal since observation became enabled. **/
   virtual void on_scheduler_entry( bool /*is_worker*/ ) {}
   
   //! Exit notification
   /** Invoked from inside observe(false) call and whenever a worker leaves the
    arena this observer is associated with.
    Obsolete semantics. For global observers it is called by a thread before
    the first steal since observation became enabled. **/
   virtual void on_scheduler_exit( bool /*is_worker*/ ) {}
   
   //! Destructor automatically switches observation off if it is enabled.
   virtual ~task_scheduler_observer_v3() { if(my_proxy) observe(false);}
};

} // namespace internal

namespace interface6 {

class task_scheduler_observer : public internal::task_scheduler_observer_v3 {
   friend class internal::task_scheduler_observer_v3;
   friend class tbb::detail::r1::observer_proxy;
   friend class tbb::detail::r1::observer_list;
   
   /** Negative numbers with the largest absolute value to minimize probability
    of coincidence in case of a bug in busy count usage. **/
   // TODO: take more high bits for version number
   static const intptr_t v6_trait = (intptr_t)((~(uintptr_t)0 >> 1) + 1);
   
   //! contains task_arena pointer or tag indicating local or global semantics of the observer
   intptr_t my_context_tag;
   enum { global_tag = 0, implicit_tag = 1 };
   
public:
   //! Construct local or global observer in inactive state (observation disabled).
   /** For a local observer entry/exit notifications are invoked whenever a worker
    thread joins/leaves the arena of the observer's owner thread. If a thread is
    already in the arena when the observer is activated, the entry notification is
    called before it executes the first stolen task. **/
   /** TODO: Obsolete.
    Global observer semantics is obsolete as it violates master thread isolation
    guarantees and is not composable. Thus the current default behavior of the
    constructor is obsolete too and will be changed in one of the future versions
    of the library. **/
   explicit task_scheduler_observer( bool local = false ) {
      my_context_tag = local? implicit_tag : global_tag;
   }
   
   //! Construct local observer for a given arena in inactive state (observation disabled).
   /** entry/exit notifications are invoked whenever a thread joins/leaves arena.
    If a thread is already in the arena when the observer is activated, the entry notification
    is called before it executes the first stolen task. **/
   explicit task_scheduler_observer( task_arena & a) {
      my_context_tag = (intptr_t)&a;
   }
   
   /** Destructor protects instance of the observer from concurrent notification.
    It is recommended to disable observation before destructor of a derived class starts,
    otherwise it can lead to concurrent notification callback on partly destroyed object **/
   virtual ~task_scheduler_observer() { if(my_proxy) observe(false); }
   
   //! Enable or disable observation
   /** Warning: concurrent invocations of this method are not safe.
    Repeated calls with the same state are no-ops. **/
   void observe( bool state=true ) {
      if( state && !my_proxy ) {
         __TBB_ASSERT( !my_busy_count, "Inconsistent state of task_scheduler_observer instance");
         my_busy_count.store(v6_trait);
      }
      internal::task_scheduler_observer_v3::observe(state);
   }
};

} // namespace interface6

} // namespace tbb

namespace tbb {
namespace internal {

DLL_EXPORT
void __TBB_EXPORTED_FUNC task_scheduler_observer_v3::observe( bool enable ) {
   auto* tso = (tbb::detail::d1::task_scheduler_observer*) (this);
   tbb::detail::r1::observe(*tso, enable);
}

} // namespace internal
} // namespace tbb

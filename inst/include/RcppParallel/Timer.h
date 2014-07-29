#ifndef __RCPP_PARALLEL_TIMER__
#define __RCPP_PARALLEL_TIMER__

namespace RcppParallel {
    typedef uint64_t nanotime_t;

    template <typename Timer>
    class ProportionTimer {
    public:
        ProportionTimer() : timer(), n(0){}
        
        ProportionTimer( nanotime_t origin ) : timer(origin), n(0){}
        
        inline operator SEXP() const {
            Rcpp::NumericVector out = (SEXP)timer ;
            out.attr("n") = n ;
            return out ;
        }
        
        inline nanotime_t origin() const{
            return timer.origin() ;
        }
        
        inline int get_n() const {
            return n ;    
        }
        
        inline void step( const std::string& name) {
            timer.step(name) ;    
        }
        
        Timer timer ;
        int n ;
    } ;
    
    template <typename Timer>
    class SingleTimer {
    public:
        SingleTimer() : timer(){}
        
        inline operator SEXP(){
            Rcpp::List out = Rcpp::List::create(timer) ;
            out.attr("class") = Rcpp::CharacterVector::create( "SingleTimer", "Timer" );
            return out ;
        }
        
        inline void step( const char* name ){
            timer.step(name) ;    
        }
        
    private:
        Timer timer ;
    } ;
    
    template <typename Timer>
    class FixedSizeTimers {
    public:
        FixedSizeTimers( int n ) : timers(n){}
        
        inline Timer& get(int i) {
            return timers[i] ;
        }
        
        inline operator SEXP(){
            Rcpp::List out = wrap(timers) ;
            out.attr("class") = Rcpp::CharacterVector::create("FixedSizeTimers", "Timer") ;
            return out ;
        }
        
        
    private:
        std::vector<Timer> timers ;
    } ;
    
    template <typename Timer, typename Mutex, typename Locker>
    class TimersList {
    public:
        
        TimersList(): timers(){}
        
        Timer& get_new_timer(){
            Locker lock(mutex) ;
            if( timers.empty() ) {
                timers.push_back( Timer() ) ;
            } else {
                timers.push_back( Timer( timers.front().origin() ) ) ;
            }
            return timers.back() ;
        }
        
        inline operator SEXP(){
            Rcpp::List data = wrap(timers) ;
            data.attr("class") = Rcpp::CharacterVector::create( "TimersList" , "Timer" ) ;
            return data ;
        }
        
    private:
        TimersList( const TimersList& ) ;
        std::list<Timer> timers ;
        Mutex mutex ;
        
    } ;
    
    template <typename Reducer, typename Timer, typename Mutex, typename Locker>
    class TimedReducer : public Worker {
    public:
        typedef TimersList<ProportionTimer<Timer>,Mutex,Locker> Timers ; 
        
        Reducer* reducer ;
        Timers& timers ;
        ProportionTimer<Timer>& timer ;
        bool owner ;
        
        TimedReducer( Reducer& reducer_, Timers& timers_) : 
            reducer(&reducer_), 
            timers(timers_), 
            timer(timers.get_new_timer()), 
            owner(false)
        {
            timer.step("init");
        }
        
        TimedReducer( const TimedReducer& other, Split s) : 
            reducer( new Reducer(*other.reducer, s) ), 
            timers( other.timers ), 
            timer( timers.get_new_timer() ), 
            owner(true)
        {
            timer.step("init") ;
        }
        
        ~TimedReducer(){
            if(owner) {
                delete reducer ;
            }
            reducer = 0 ;
        }
        
        inline void operator()( size_t begin, size_t end){
            timer.n += (end-begin) ;
            timer.step("start") ;
            (*reducer)(begin, end) ;
            timer.step("work") ;
        }
        
        inline void join(const TimedReducer& rhs){
            timer.n += rhs.timer.n ;
            timer.step("start") ;
            (*reducer).join(*rhs.reducer) ;
            timer.step("join") ;
        }
        
        inline Rcpp::List get() const {
            timer.step("start") ;
            Rcpp::List res = Rcpp::List::create( (SEXP)timers, reducer->get() );
            timer.step("structure") ;
            return res ;
        }
        
    private:
        // just to be on the safe side, making sure these are not called
        TimedReducer() ;
        TimedReducer( const TimedReducer& ) ;
    } ;
    
    
} // namespace RcppParallel


#endif // __RCPP_PARALLEL_COMMON__

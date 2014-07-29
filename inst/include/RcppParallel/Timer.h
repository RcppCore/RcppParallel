#ifndef __RCPP_PARALLEL_TIMER__
#define __RCPP_PARALLEL_TIMER__

namespace RcppParallel {
    typedef uint64_t nanotime_t;

    template <typename Timer>
    class ProportionTimer {
    public:
        ProportionTimer() : 
            timer(), n(0), id(0)
        {}
        
        ProportionTimer( nanotime_t origin, int id_ ) : 
            timer(origin), n(0), id(id_)
        {}
        
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
        int id ;
        
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
        
        TimersList(): timers(){
            timers.push_back( ProportionTimer<Timer>() );
            childs.push_back( std::vector<int>() ) ;
        }
        
        ProportionTimer<Timer>& get_new_timer(int parent_id){
            Locker lock(mutex) ;
            int id = timers.size() ;
            timers.push_back( ProportionTimer<Timer>( timers.front().origin(), id ) ) ;
            childs.push_back( std::vector<int>() );
            std::list<std::vector<int> >::iterator it = childs.begin() ;
            for(int i=0; i<parent_id; i++) ++it ;
            it->push_back(id) ;
            return timers.back() ;
        }
        
        inline operator SEXP(){
            int n = timers.size() ;
            Rcpp::List data(n) ;
            typename std::list<ProportionTimer<Timer> >::const_iterator timers_it = timers.begin() ;
            std::list<std::vector<int> >::const_iterator childs_it = childs.begin() ;
            for( int i=0; i<n; i++, ++timers_it, ++childs_it ){
                Rcpp::NumericVector x = (SEXP)*timers_it ;
                x.attr("childs") = Rcpp::wrap( *childs_it ) ;
                x.attr("id") = timers_it->id ;
                data[i] = x ;
            }
            data.attr("class") = Rcpp::CharacterVector::create( "TimersList" , "Timer" ) ;
            return data ;
        }
        
        inline ProportionTimer<Timer>& front(){ 
            return timers.front(); 
        }
        
        std::list<ProportionTimer<Timer> > timers ;
        std::list<std::vector<int> > childs ;
        Mutex mutex ;
        
    private:
        TimersList( const TimersList& ) ;
    
    } ;
    
    template <typename Reducer, typename Timer, typename Mutex, typename Locker>
    class TimedReducer : public Worker {
    public:
        typedef TimersList<Timer,Mutex,Locker> Timers ; 
        
        Reducer* reducer ;
        Timers& timers ;
        ProportionTimer<Timer>& timer ;
        bool owner ;
        
        TimedReducer( Reducer& reducer_, Timers& timers_) : 
            reducer(&reducer_), 
            timers(timers_), 
            timer(timers.get_new_timer(0)), 
            owner(false)
        {
            timer.step("init");
        }
        
        TimedReducer( const TimedReducer& other, Split s) : 
            reducer( new Reducer(*other.reducer, s) ), 
            timers( other.timers ), 
            timer( timers.get_new_timer(other.timer.id) ),
            owner(true)
        {
            timer.step("init") ;
        }
        
        ~TimedReducer(){
            if(owner && reducer) {
                delete reducer ;
            }
            reducer = 0 ;
        }
        
        inline void operator()( size_t begin, size_t end){
            timer.n += (end-begin) ;
            timer.step("start") ;
            reducer->operator()(begin, end) ;
            timer.step("work") ;
        }
        
        inline void join(const TimedReducer& rhs){
            timer.n += rhs.timer.n ;
            timer.step("start") ;
            reducer->join(*rhs.reducer) ;
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

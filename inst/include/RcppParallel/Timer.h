#ifndef __RCPP_PARALLEL_TIMER__
#define __RCPP_PARALLEL_TIMER__

namespace RcppParallel {
    
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
    
    
} // namespace RcppParallel


#endif // __RCPP_PARALLEL_COMMON__

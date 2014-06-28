/*
    Copyright 2005-2014 Intel Corporation.  All Rights Reserved.

    This file is part of Threading Building Blocks.

    Threading Building Blocks is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    Threading Building Blocks is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Threading Building Blocks; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, you may use this file as part of a free software
    library without restriction.  Specifically, if other files instantiate
    templates or use macros or inline functions from this file, or you compile
    this file and link it with other files to produce an executable, this
    file does not by itself cause the resulting executable to be covered by
    the GNU General Public License.  This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/

#include "harness.h"
#include "tbb/flow_graph.h"
#include "tbb/atomic.h"
#include "tbb/task_scheduler_init.h"

const int L = 10;
const int N = 1000;

template< typename T >
struct serial_receiver : public tbb::flow::receiver<T> {
   T next_value;

   serial_receiver() : next_value(T(0)) {}

   /* override */ tbb::task *try_put_task( const T &v ) {
       ASSERT( next_value++  == v, NULL );
       return const_cast<tbb::task *>(tbb::flow::interface7::SUCCESSFULLY_ENQUEUED);
   }

   /*override*/void reset_receiver() {next_value = T(0);}
};

template< typename T >
struct parallel_receiver : public tbb::flow::receiver<T> {

   tbb::atomic<int> my_count;

   parallel_receiver() { my_count = 0; }

   /* override */ tbb::task *try_put_task( const T &/*v*/ ) {
       ++my_count;
       return const_cast<tbb::task *>(tbb::flow::interface7::SUCCESSFULLY_ENQUEUED);
   }

   /*override*/void reset_receiver() {my_count = 0;}
};

template< typename T >
struct empty_sender : public tbb::flow::sender<T> {
        /* override */ bool register_successor( tbb::flow::receiver<T> & ) { return false; }
        /* override */ bool remove_successor( tbb::flow::receiver<T> & ) { return false; }
};


template< typename T >
struct put_body : NoAssign {

    tbb::flow::limiter_node<T> &my_lim;
    tbb::atomic<int> &my_accept_count;

    put_body( tbb::flow::limiter_node<T> &lim, tbb::atomic<int> &accept_count ) : 
        my_lim(lim), my_accept_count(accept_count) {}

    void operator()( int ) const {
        for ( int i = 0; i < L; ++i ) {
            bool msg = my_lim.try_put( T(i) );
            if ( msg == true )
               ++my_accept_count; 
        }
    }
};

template< typename T >
struct put_dec_body : NoAssign {

    tbb::flow::limiter_node<T> &my_lim;
    tbb::atomic<int> &my_accept_count;

    put_dec_body( tbb::flow::limiter_node<T> &lim, tbb::atomic<int> &accept_count ) : 
        my_lim(lim), my_accept_count(accept_count) {}

    void operator()( int ) const {
        int local_accept_count = 0;
        while ( local_accept_count < N ) {
            bool msg = my_lim.try_put( T(local_accept_count) );
            if ( msg == true ) {
                ++local_accept_count;
                ++my_accept_count;
                my_lim.decrement.try_put( tbb::flow::continue_msg() );
            } 
        }
    }

};

template< typename T >
void test_puts_with_decrements( int num_threads, tbb::flow::limiter_node< T >& lim ) {
    parallel_receiver<T> r;
    empty_sender< tbb::flow::continue_msg > s;
    tbb::atomic<int> accept_count;
    accept_count = 0;
    tbb::flow::make_edge( lim, r );
    lim.decrement.register_predecessor( s );
    // test puts with decrements
    NativeParallelFor( num_threads, put_dec_body<T>(lim, accept_count) );
    int c = accept_count;
    ASSERT( c == N*num_threads, NULL );
    ASSERT( r.my_count == N*num_threads, NULL );
}

//
// Tests
//
// limiter only forwards below the limit, multiple parallel senders / single receiver
// mutiple parallel senders that put to decrement at each accept, limiter accepts new messages
// 
// 
template< typename T >
int test_parallel(int num_threads) {
 
   // test puts with no decrements
   for ( int i = 0; i < L; ++i ) {
       tbb::flow::graph g;
       tbb::flow::limiter_node< T > lim(g, i);
       parallel_receiver<T> r;
       tbb::atomic<int> accept_count;
       accept_count = 0;
       tbb::flow::make_edge( lim, r );
       // test puts with no decrements
       NativeParallelFor( num_threads, put_body<T>(lim, accept_count) );
       g.wait_for_all();
       int c = accept_count;
       ASSERT( c == i, NULL );
   }

   // test puts with decrements
   for ( int i = 1; i < L; ++i ) {
       tbb::flow::graph g;
       tbb::flow::limiter_node< T > lim(g, i);
       test_puts_with_decrements(num_threads, lim);
       tbb::flow::limiter_node< T > lim_copy( lim );
       test_puts_with_decrements(num_threads, lim_copy);
   }

   return 0;
}

//
// Tests
//
// limiter only forwards below the limit, single sender / single receiver
// at reject, a put to decrement, will cause next message to be accepted
// 
template< typename T >
int test_serial() {
 
   // test puts with no decrements
   for ( int i = 0; i < L; ++i ) {
       tbb::flow::graph g;
       tbb::flow::limiter_node< T > lim(g, i);
       serial_receiver<T> r;
       tbb::flow::make_edge( lim, r );
       for ( int j = 0; j < L; ++j ) {
           bool msg = lim.try_put( T(j) );
           ASSERT( ( j < i && msg == true ) || ( j >= i && msg == false ), NULL );
       }
       g.wait_for_all();
   }

   // test puts with decrements
   for ( int i = 1; i < L; ++i ) {
       tbb::flow::graph g;
       tbb::flow::limiter_node< T > lim(g, i);
       serial_receiver<T> r;
       empty_sender< tbb::flow::continue_msg > s;
       tbb::flow::make_edge( lim, r );
       lim.decrement.register_predecessor( s );
       for ( int j = 0; j < N; ++j ) {
           bool msg = lim.try_put( T(j) );
           ASSERT( ( j < i && msg == true ) || ( j >= i && msg == false ), NULL );
           if ( msg == false ) {
               lim.decrement.try_put( tbb::flow::continue_msg() );
               msg = lim.try_put( T(j) );
               ASSERT( msg == true, NULL );
           }
       }
   }
   return 0;
}

// reported bug in limiter (http://software.intel.com/en-us/comment/1752355)
#define DECREMENT_OUTPUT 1  // the port number of the decrement output of the multifunction_node
#define LIMITER_OUTPUT 0    // port number of the integer output

typedef tbb::flow::multifunction_node<int, tbb::flow::tuple<int,tbb::flow::continue_msg> > mfnode_type;

tbb::atomic<size_t> emit_count;
tbb::atomic<size_t> emit_sum;
tbb::atomic<size_t> receive_count;
tbb::atomic<size_t> receive_sum;

struct mfnode_body {
    int max_cnt;
    tbb::atomic<int>* my_cnt;
    mfnode_body(const int& _max, tbb::atomic<int> &_my) : max_cnt(_max), my_cnt(&_my)  { }
    void operator()(const int &/*in*/, mfnode_type::output_ports_type &out) {
        int lcnt = ++(*my_cnt);
        if(lcnt > max_cnt) {
            return;
        }
        // put one continue_msg to the decrement of the limiter.
        if(!tbb::flow::get<DECREMENT_OUTPUT>(out).try_put(tbb::flow::continue_msg())) {
            ASSERT(false,"Unexpected rejection of decrement");
        }
        {
            // put messages to the input of the limiter_node until it rejects.
            while( tbb::flow::get<LIMITER_OUTPUT>(out).try_put(lcnt) ) {
                emit_sum += lcnt;
                ++emit_count;
            }
        }
    }
};

struct fn_body {
    int operator()(const int &in) {
        receive_sum += in;
        ++receive_count;
        return in;
    }
};

//                   +------------+
//    +---------+    |            v
//    | mf_node |0---+       +----------+          +----------+
// +->|         |1---------->| lim_node |--------->| fn_node  |--+
// |  +---------+            +----------+          +----------+  |
// |                                                             |
// |                                                             |
// +-------------------------------------------------------------+
//
void
test_multifunction_to_limiter(int _max, int _nparallel) {
    tbb::flow::graph g;
    emit_count = 0;
    emit_sum = 0;
    receive_count = 0;
    receive_sum = 0;
    tbb::atomic<int> local_cnt;
    local_cnt = 0;
    mfnode_type mf_node(g, tbb::flow::unlimited, mfnode_body(_max, local_cnt));
    tbb::flow::function_node<int, int> fn_node(g, tbb::flow::unlimited, fn_body());
    tbb::flow::limiter_node<int> lim_node(g, _nparallel);
    tbb::flow::make_edge(tbb::flow::output_port<LIMITER_OUTPUT>(mf_node), lim_node);
    tbb::flow::make_edge(tbb::flow::output_port<DECREMENT_OUTPUT>(mf_node), lim_node.decrement);
    tbb::flow::make_edge(lim_node, fn_node);
    tbb::flow::make_edge(fn_node, mf_node);
    mf_node.try_put(1);
    g.wait_for_all();
    ASSERT(emit_count == receive_count, "counts do not match");
    ASSERT(emit_sum == receive_sum, "sums do not match");

    // reset, test again
    g.reset();
    emit_count = 0;
    emit_sum = 0;
    receive_count = 0;
    receive_sum = 0;
    local_cnt = 0;;
    mf_node.try_put(1);
    g.wait_for_all();
    ASSERT(emit_count == receive_count, "counts do not match");
    ASSERT(emit_sum == receive_sum, "sums do not match");
}


void
test_continue_msg_reception() {
    tbb::flow::graph g;
    tbb::flow::limiter_node<int> ln(g,2);
    tbb::flow::queue_node<int>   qn(g);
    tbb::flow::make_edge(ln, qn);
    ln.decrement.try_put(tbb::flow::continue_msg());
    ln.try_put(42);
    g.wait_for_all();
    int outint;
    ASSERT(qn.try_get(outint) && outint == 42, "initial put to decrement stops node");
}


//
// This test ascertains that if a message is not successfully put
// to a successor, the message is not dropped but released.
//

using namespace tbb::flow;
void test_reserve_release_messages() {
    graph g;

    //making two queue_nodes: one broadcast_node and one limiter_node
    queue_node<int> input_queue(g);
    queue_node<int> output_queue(g);
    broadcast_node<continue_msg> broad(g);
    limiter_node<int> limit(g,2,1); //threshold of 2

    //edges
    make_edge(input_queue, limit);
    make_edge(limit, output_queue);
    make_edge(broad,limit.decrement); 

    int list[4] = {19, 33, 72, 98}; //list to be put to the input queue

    input_queue.try_put(list[0]); // succeeds
    input_queue.try_put(list[1]); // succeeds
    input_queue.try_put(list[2]); // fails, stored in upstream buffer
    g.wait_for_all();

    remove_edge(limit, output_queue); //remove successor

    //sending continue messages to the decrement port of the limiter
    broad.try_put(continue_msg());
    broad.try_put(continue_msg()); //failed message retrieved.
    g.wait_for_all();

    make_edge(limit, output_queue); //putting the successor back

    broad.try_put(continue_msg());
    broad.try_put(continue_msg());  //drop the count

    input_queue.try_put(list[3]);  //success
    g.wait_for_all();

    int var=0;

    for (int i=0; i<4; i++){
    output_queue.try_get(var);
    ASSERT(var==list[i], "some data dropped, input does not match output");
    g.wait_for_all();
  }
}


int TestMain() { 
    for (int i = 1; i <= 8; ++i) {
        tbb::task_scheduler_init init(i);
        test_serial<int>();
        test_parallel<int>(i);
    }
    test_continue_msg_reception();
    test_multifunction_to_limiter(30,3);
    test_multifunction_to_limiter(300,13);
    test_multifunction_to_limiter(3000,1);
    test_reserve_release_messages();
   return Harness::Done;
}

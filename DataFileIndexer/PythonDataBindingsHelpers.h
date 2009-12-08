/*
 *  PythonDataBindingsHelpers.h
 *  DataFileIndexer
 *
 *  Created by David Cox on 12/8/09.
 *  Copyright 2009 Harvard University. All rights reserved.
 *
 */

#ifndef PYTHON_DATA_BINDINGS_HELPERS_H_
#define PYTHON_DATA_BINDINGS_HELPERS_H_

#include <Scarab/scarab.h>
#include <Scarab/scarab_utilities.h>
#include <boost/python.hpp>
#include "dfindex.h"
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <python.h>

using namespace boost;
namespace bp = boost::python;

extern double scarab_extract_float(ScarabDatum *datum);

class PythonDataFile {
    std::string file_name;
    shared_ptr<dfindex> indexer;
    
    
public:
    
    PythonDataFile(std::string _file_name);    
    
    void open();    
    void close();    
    
    bool exists();
    
    bool loaded();    
    bool valid();
    
    MonkeyWorksTime minimum_time();
    MonkeyWorksTime maximum_time();
    
    std::vector<EventWrapper> test_function(int number);    
    
    std::vector<EventWrapper> fetch_all_events();
    
    std::vector<EventWrapper> fetch_events1(bp::list codes);    
    std::vector<EventWrapper> fetch_events2(bp::list codes, const MonkeyWorksTime lower_bound);    
    
    std::vector<EventWrapper> fetch_events3(bp::list codes,
                                            const MonkeyWorksTime lower_bound, 
                                            const MonkeyWorksTime upper_bound);
};



// A simple, non-indexing stream (e.g. file / socket) reader for 
// python wrapping
class PythonDataStream {
    std::string uri;
    
    ScarabSession *session;
    
public:
    
    PythonDataStream(std::string _uri);
    
    void open();
    
    void close();    
    
    shared_ptr<EventWrapper> read_event();

};    

// Convert a ScarabDatum into a corresponding Python object
extern PyObject *convert_scarab_to_python(ScarabDatum *datum);


extern PyObject *extract_event_value(EventWrapper e);


//struct eventvector2pysequence{
//    
//    typedef boost::tuples::tuple< float, float, float> colour_tuple_type;
//    
//    typedef bpl::from_py_sequence< colour_tuple_type > converter_type;
//    
//    static void* convertible(PyObject* obj){
//        return converter_type::convertible( obj );
//    }
//    
//    static void
//    construct( PyObject* obj, bpl::converter::rvalue_from_python_stage1_data* data){
//        typedef bpl::converter::rvalue_from_python_storage<colour_t> colour_storage_t;
//        colour_storage_t* the_storage = reinterpret_cast<colour_storage_t*>( data );
//        void* memory_chunk = the_storage->storage.bytes;
//        
//        float red(0.0), green(0.0), blue(0.0);
//        boost::tuples::tie(red, green, blue) = converter_type::to_c_tuple( obj );
//        
//        colour_t* colour = new (memory_chunk) colour_t(red, green, blue);
//        data->convertible = memory_chunk;
//    }
//};
//
//void register_pytuple2colour(){
//    converter::registry::push_back(  &pytuple2colour::convertible
//                                        , &pytuple2colour::construct
//                                        , bpl::type_id<colour_t>() );
//}


#endif

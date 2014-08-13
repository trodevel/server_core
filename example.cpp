/*

Example.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Id: example.cpp 657 2014-07-02 16:59:31Z serge $

#include <cstdio>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "../utils/wrap_mutex.h"    // THREAD_SLEEP_MS

#include "request_parser.h"         // RequestParser
#include "str_helper.h"             // StrHelper
#include "server.h"                 // Server
#include "i_handler.h"              // IHandler

class Handler: public virtual server_core::IHandler
{
    virtual const std::string handle( const std::string & s )
    {
        std::cout << "got request '" << s << "'" << std::endl;

        server_core::GenericRequest r = server_core::RequestParser::to_generic_request( s );

        std::string parsed_s = server_core::StrHelper::to_string( r );

        std::cout << "parsed = " << parsed_s << std::endl;

        return "OK - processed '" + parsed_s + "'";
    }
};

void dummy_thread()
{
    std::cout << "dummy_thread(): started" << std::endl;

    while( true )
    {

        std::cout << "type 'exit' to exit" << std::endl;

        std::string input;

        std::getline( std::cin, input );

        if( input == "exit" || input == "quit" )
            break;

        THREAD_SLEEP_MS( 3 );
    }

    std::cout << "dummy_thread(): exited" << std::endl;
}

int main()
{
    printf( "Hello, world\n" );

    try
    {
        server_core::Server::Config cfg = { 1234, 5, 2 };

        server_core::Server s;

        Handler h;

        s.init( cfg, &h );

        s.start_listen();

        boost::thread_group tg;

        tg.create_thread( &dummy_thread );

        tg.join_all();

        s.shutdown( 2, 2 );

        s.join_client_threads();

        std::cout << "exit" << std::endl;
    }
    catch( std::exception& e )
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}

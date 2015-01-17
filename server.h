/*

Server.

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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#include <boost/thread.hpp>         // boost::mutex

#include "../threcon/i_controllable.h"  // IControllable
#include "../tcpserv/server.h"  // Server, ServicePtr
#include "../utils/types.h"     // uint16, uint32

#include "namespace_lib.h"      // NAMESPACE_SERVER_CORE_START

NAMESPACE_SERVER_CORE_START

class IHandler;

class Server: public tcpserv::Server, public virtual threcon::IControllable
{
public:
    typedef tcpserv::Server::Config Config;

public:

    Server();

    bool init(
            const Config    & cfg,
            IHandler        * handler );

    virtual tcpserv::ServicePtr create_service( boost::asio::ip::tcp::socket* socket );

    // interface threcon::IControllable
    virtual bool shutdown();


private:

    bool is_inited__() const;

private:
    mutable boost::mutex        mutex_;

    boost::thread   broadcast_thread_;

    IHandler        * handler_;

};


NAMESPACE_SERVER_CORE_END

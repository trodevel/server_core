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

// $Revision: 6658 $ $Date:: 2017-04-18 #$ $Author: serge $

#include <mutex>                // std::mutex
#include <thread>               // std::thread

#include "../threcon/i_controllable.h"  // IControllable
#include "../tcpserv/server.h"  // Server, ServicePtr

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
            uint32_t        log_id,
            uint32_t        log_id_service,
            IHandler        * handler );

    virtual tcpserv::ServicePtr create_service( boost::asio::ip::tcp::socket* socket );

    // interface threcon::IControllable
    virtual bool shutdown();


private:

    bool is_inited__() const;

private:
    mutable std::mutex      mutex_;

    std::thread             broadcast_thread_;

    uint32_t                log_id_;
    uint32_t                log_id_service_;
    IHandler                * handler_;
};


NAMESPACE_SERVER_CORE_END

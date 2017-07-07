/*
 * Copyright (C) 2013, Maoxu Li. Email: maoxu@lebula.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NET_BASE_HTTP_CLIENT_HPP
#define NET_BASE_HTTP_CLIENT_HPP

#include "HttpMessage.hpp"
#include "TcpConnector.hpp"
#include "TcpConnection.hpp"

NET_BASE_BEGIN

class EventLoop;
class HttpClient
{
public:
    HttpClient(EventLoop* loop);
    virtual ~HttpClient();

    bool Connect(const char* host, unsigned short port);

    // Send out a request message
    void SendRequest(HttpRequest* request);

protected:
    // TcpConnection::ConnectedCallback
    void OnConnected(TcpConnection* conn);

    // TcpConnection::ReceivedCallback
    void OnReceived(TcpConnection* conn, ByteStream* stream);

    // TcpConnection::ClosedCallback
    void OnClosed(TcpConnection* conn);

protected:
    // Event loop on thread
    EventLoop* mLoop;

    // TcpConnector
    TcpConnector mConnector;

    // Established HTTP connection
    TcpConnection* mConnection;
    HttpResponse mResponse;

    // Handle incoming response message
    virtual void HandleResponse(HttpResponse* response);
};

NET_BASE_END

#endif
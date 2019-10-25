#include "pch.h"
#include "HttpServer.h"

#include <cpprest/http_listener.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class CHttpServerImpl : public CHttpServer
{
	http_listener m_listener;
public:
	CHttpServerImpl(const std::wstring & address) : m_listener(address)
	{
		m_listener.support([this](http_request req) {handler(req); });
	}

	// CHttpServer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual std::future<void> StartAsync() override
	{
		return std::async([this] { m_listener.open().wait(); });
	}
	virtual std::future<void> StopAsync() override
	{
		return std::async([this] { m_listener.close().wait(); });
	}

private:
	void handler(http_request req)
	{
		std::wclog << req.method() << std::endl;
		req.reply(status_codes::OK);
	}
};


std::shared_ptr<CHttpServer> CHttpServer_CreateInstance(const std::wstring & address)
{
	return std::make_shared<CHttpServerImpl>(address);
}

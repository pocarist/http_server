#pragma once
class CHttpServer
{
public:
	virtual std::future<void> StartAsync() = 0;
	virtual std::future<void> StopAsync() = 0;

protected:
	virtual ~CHttpServer() { }
};

std::shared_ptr<CHttpServer> CHttpServer_CreateInstance(const std::wstring& address);


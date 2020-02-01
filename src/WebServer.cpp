#include "../include/WebServer.h"
/*#include <iostream>
#include "../include/Utils.h"
#include "../include/Inputs.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

WebServer::WebServer(utility::string_t url)
	:m_listener(url)
{
	m_listener.support(methods::GET, handle_get);
	m_listener.support(methods::POST, handle_post);
}

void WebServer::handle_request(http_request request, std::function<void(json::value const&, json::value&)> action)
{
	auto answer = json::value::object();

	request
		.extract_json()
		.then([&answer, &action](pplx::task<json::value> task)
		{
			try
			{
				auto const& jvalue = task.get();
				display_json(jvalue, L"R: ");

				if (!jvalue.is_null())
				{
					action(jvalue, answer);
				}
			}
			catch (http_exception const& e)
			{
				std::wcout << e.what() << std::endl;
			}
		})
		.wait();

	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
}

void WebServer::handle_get(http_request request)
{
	std::cout << "Handle GET" << std::endl;

	handle_request(
		request,
		[](json::value const& jvalue, json::value& answer)
	{
		Inputs inputs = Inputs(jvalue.as_object());
		run_algo(&inputs, Algo(GLUTTON_BREADTH), answer);
	});
}

void WebServer::handle_post(http_request request)
{
	std::cout << "Handle POST" << std::endl;

	handle_request(
		request,
		[](json::value const& jvalue, json::value& answer)
	{
		Inputs inputs = Inputs(jvalue.as_object());
		run_algo(&inputs, Algo(GLUTTON_BREADTH), answer);
	});
}

void WebServer::run()
{
	try
	{
		open().wait();

		std::cout << "Listening to request..." << std::endl << std::endl;

		while (true);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
*/
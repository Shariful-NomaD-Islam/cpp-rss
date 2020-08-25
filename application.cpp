#include <iostream>
#include <served/served.hpp>
#include <served/plugins.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/bind/bind.hpp>

#define VERSION "0.0.1"

using namespace boost::placeholders;

class RestEndpoint
{
private:
    served::multiplexer mux;
    std::string post_value = "-1";

public:
    RestEndpoint()
    {
        mux.use_after(served::plugin::access_log);
        mux.handle("/api/version")
            .get([&](served::response &res, const served::request &req) {
                boost::property_tree::ptree root;
                std::string response;
                std::stringstream ss;

                root.put("API Version", VERSION);

                boost::property_tree::json_parser::write_json(ss, root, true);
                res << ss.str();
            });
        mux.handle("/api/get")
            .get([&](served::response &res, const served::request &req) {
                boost::property_tree::ptree root;
                std::string response;
                std::stringstream ss;

                root.put("Post Value", post_value);

                boost::property_tree::json_parser::write_json(ss, root, true);
                res << ss.str();
            });

        mux.handle("/api/greeting")
            .get([&](served::response &res, const served::request &req) {
                std::string name = req.query["name"];
                boost::property_tree::ptree root;
                std::string response;
                std::stringstream ss;

                root.put("Greeting", name);

                boost::property_tree::json_parser::write_json(ss, root, true);
                res << ss.str();
            });
        mux.handle("/api/named-user/{id}")
            .get([](served::response &res, const served::request &req) {
                boost::property_tree::ptree root;
                std::string response;
                std::stringstream ss;

                root.put("User name", req.params["id"]);

                boost::property_tree::json_parser::write_json(ss, root, true);
                res << ss.str();
            });
        mux.handle("/api/patern-user/{id:\\d+}")
            .get([](served::response &res, const served::request &req) {
                boost::property_tree::ptree root;
                std::string response;
                std::stringstream ss;

                root.put("Patern User ID", req.params["id"]);

                boost::property_tree::json_parser::write_json(ss, root, true);
                res << ss.str();
            });
        mux.handle("/api/post/{id:\\d+}")
            .post([&](served::response &res, const served::request &req) {
                if (req.header("Content-Type") != "application/json")
                {
                    served::response::stock_reply(400, res);
                    return;
                }

                boost::property_tree::ptree root;
                std::string response = req.body();
                std::stringstream ss(response);

                boost::property_tree::json_parser::read_json(ss, root);
                post_value = root.get<std::string>("key");
                res << root.get<std::string>("key");
            });
    }

    void start(std::string const &ip = "127.0.0.1", std::string const &port = "8123")
    {
        std::cout << "Available API example:" << std::endl;
        std::cout << "  curl \"http://" << ip << ":" << port << "/api/version\"" << std::endl;
        std::cout << "  curl \"http://" << ip << ":" << port << "/api/greeting?name=_NAME_\"" << std::endl;
        std::cout << "  curl \"http://" << ip << ":" << port << "/api/named-user/nomad\"" << std::endl;
        std::cout << "  curl \"http://" << ip << ":" << port << "/api/patern-user/8\"" << std::endl;
        std::cout << "  curl \"http://" << ip << ":" << port << "/api/get\"" << std::endl;
        std::cout << "  curl -d '{ \"key\": \"value\" }' -H \"Content-Type: application/json\" -X POST http://" << ip << ":" << port << "/api/post/45" << std::endl;

        served::net::server server(ip, port, mux);
        server.run(10);
    }
};

int main(int argc, const char *argv[])
{
    class RestEndpoint rest_endpoint;

    std::string ip = "localhost";
    std::string port = "9091";

    if (argc == 2)
    {
        port = argv[1];
    }

    rest_endpoint.start(ip, port);
}

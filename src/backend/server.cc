#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>

#include "boost/asio/io_service.hpp"
#include "boost/asio/signal_set.hpp"
#include "boost/thread.hpp"

#include "net/http/server/shutdown_handler.hpp"

#include "footrouting/backend/http_server.h"

using net::http::server::shutdown_handler;

template <typename T>
using shutd_hdr_ptr = std::unique_ptr<shutdown_handler<T>>;

namespace footrouting::backend {

auto run(boost::asio::io_service& ios) {
  return [&ios]() {
    while (true) {
      try {
        ios.run();
        break;
      } catch (std::exception const& e) {
        std::cout << "unhandled error: " << e.what();
      } catch (...) {
        std::cout << "unhandled unknown error";
      }
    }
  };
}

void ppr_server(routing_graph const& rg, std::string const& http_host,
                std::string const& http_port, int num_threads) {
  std::cout << "Starting HTTP server on http://" << http_host << ":"
            << http_port << "/" << std::endl;

  boost::asio::io_service ios, thread_pool;
  http_server http(ios, thread_pool, rg);
  shutd_hdr_ptr<http_server> http_shutdown_handler;

  http.listen(http_host, http_port);
  http_shutdown_handler =
      std::make_unique<shutdown_handler<http_server>>(ios, http);

  net::http::server::io_service_shutdown shutd(ios);
  shutdown_handler<net::http::server::io_service_shutdown> shutdown(ios, shutd);

  boost::asio::io_service::work work(thread_pool);
  std::vector<std::thread> threads(
      static_cast<unsigned>(std::max(1, num_threads)));
  for (auto& t : threads) {
    t = std::thread(run(thread_pool));
  }

  run(ios)();
  thread_pool.stop();
  std::for_each(begin(threads), end(threads), [](std::thread& t) { t.join(); });
}

}  // namespace footrouting::backend

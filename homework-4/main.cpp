#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace {

using Ip = std::array<int, 4>;

Ip parse_ip(const std::string& text) {
    Ip ip{0, 0, 0, 0};
    std::stringstream stream(text);
    std::string part;

    for (std::size_t i = 0; i < ip.size(); ++i) {
        if (!std::getline(stream, part, '.')) {
            throw std::runtime_error("Invalid IP format");
        }
        ip[i] = std::stoi(part);
    }

    return ip;
}

void print_ip(const Ip& ip) {
    std::cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3] << '\n';
}

template <typename Predicate>
void print_filtered(const std::vector<Ip>& ips, Predicate predicate) {
    for (const Ip& ip : ips) {
        if (predicate(ip)) {
            print_ip(ip);
        }
    }
}

}  // namespace

int main() {
    std::vector<Ip> ips;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        const std::size_t tab_pos = line.find('\t');
        const std::string ip_text = line.substr(0, tab_pos);
        ips.push_back(parse_ip(ip_text));
    }

    std::sort(ips.begin(), ips.end(), std::greater<Ip>{});

    print_filtered(ips, [](const Ip&) { return true; });
    print_filtered(ips, [](const Ip& ip) { return ip[0] == 1; });
    print_filtered(ips, [](const Ip& ip) { return ip[0] == 46 && ip[1] == 70; });
    print_filtered(ips, [](const Ip& ip) {
        return std::any_of(ip.begin(), ip.end(), [](int octet) { return octet == 46; });
    });

    return 0;
}

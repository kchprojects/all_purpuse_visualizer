#pragma once
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace apv {
class MenuItem {
  std::string label_;
  std::function<void()> trigger_response_;
  std::optional<std::function<void()>> hover_response_;

public:
  MenuItem(std::string label, std::function<void()> trigger_repose,
           std::optional<std::function<void()>> hover_response = {})
      : label_{std::move(label)}, trigger_response_{std::move(trigger_repose)},
        hover_response_{std::move(hover_response)} {}

  const std::string &label() const { return label_; };
  void trigger() const { trigger_response_(); }
  void hover() const {
    if (hover_response_.has_value()) {
      (*hover_response_)();
    }
  }
};

class MenuTab {
  std::string label_;
  std::optional<std::function<void()>> hover_response_;
  std::vector<MenuItem> items_;

public:
  MenuTab(std::string label,
          std::optional<std::function<void()>> hover_response = {},
          std::vector<MenuItem> items = {})
      : label_{std::move(label)},
        hover_response_{std::move(hover_response)}, items_{std::move(items)} {}

  const std::string &label() const { return label_; }
  void hover() const {
    if (hover_response_.has_value()) {
      (*hover_response_)();
    }
  }
  const auto& items() const { return items_; }
};

using MenuBar = std::vector<MenuTab>;

} // namespace apv

#pragma once
#include <variant>
#include <memory>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <assert.h>

namespace json {
  class object;
  class value;
  using str_ptr = std::unique_ptr<std::string>;
  using obj_ptr = std::unique_ptr<object>;
  using array_ptr = std::unique_ptr<std::vector<value>>;
  enum class token_type {
			 object_start,
			 object_end,
			 array_start,
			 array_end,
			 colon,
			 comma,
			 str,
			 none_str,
  };

  struct token {
    std::string text = "";
    token_type type = token_type::none_str;
    void clear() { text = ""; type = token_type::none_str; };
  };

  
  class value {
  public:
    value(const value& v);
    value(value&& v) {var = std::move(v.var);};
    value(int x) : var(x){};
    value(float x) : var(x){};
    value(bool x) : var(x){};
    value(const std::string& x) { var = std::make_unique<std::string>(x); };
    value(const object& obj) { var = std::make_unique<object>(obj); };
    value(const std::vector<value>& arr) { var = std::make_unique<std::vector<value>>(arr);};

    value& operator=(const value& v) {
      value tv(v);
      this->var = std::move(tv.var);
      return *this;					
    }
    value& operator=(value&& v) {
      this->var = std::move(v.var);
      return *this;
    }
    value& operator[](std::string_view key) { return const_cast<value&> (*this)[key]; };
    value& operator[](std::size_t index) { return const_cast<value&> (*this)[index]; };
    const value& operator[](std::string_view key) const;
    const value& operator[](std::size_t index) const;

    int get_int() const { return std::get<int>(var); };
    float get_float() const { return std::get<float>(var); };
    bool get_bool() const { return std::get<bool>(var); };
    std::string& get_string() { return *(std::get<str_ptr>(var)); };
    const std::string& get_string() const { return *(std::get<str_ptr>(var)); };
    object& get_object() { return *(std::get<obj_ptr>(var)); };
    const object& get_object() const { return *(std::get<obj_ptr>(var)); };
    std::vector<value>& get_array() { return *(std::get<array_ptr>(var)); };
    const std::vector<value>& get_array() const { return *(std::get<array_ptr>(var)); };

    bool is_int() const { return std::holds_alternative<int>(var); };
    bool is_float() const { return std::holds_alternative<float>(var); };
    bool is_bool() const { return std::holds_alternative<bool>(var); };
    bool is_string() const { return std::holds_alternative<str_ptr>(var); };
    bool is_object() const { return std::holds_alternative<obj_ptr>(var); };
    bool is_array() const { return std::holds_alternative<array_ptr>(var); };

    friend std::ostream& operator<<(std::ostream& output, const value& val);
  private:
    std::variant<int, float, bool, str_ptr, obj_ptr, array_ptr> var;
  };

  
  class object {
  public:
    object() {};
    object(const object& obj) : keys{obj.keys}, values{obj.values} {};
    bool has_key(std::string_view key) const { return std::find(keys.begin(), keys.end(), key) != keys.end(); }
    const value& operator[](std::string_view key) const;
    value& operator[](std::string_view key) { return const_cast<object&> (*this)[key]; };
    friend object parse_file(std::string_view filename);
    friend void print_object(object& obj, int ind);
  private:
    void parse(const std::vector<token>& tokens, std::vector<token>::iterator& token_it);
    std::vector<std::string> keys;
    std::vector<value> values;
  };

  std::vector<token> lexer(std::string_view filename);
  object parse_file(std::string_view filename);
  void print_object(object& obj, int ind);
};

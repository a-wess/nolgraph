#ifndef _RAYS_JSON_
#define _RAYS_JSON_

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
  class Object;
  class Value;
  using str_ptr = std::unique_ptr<std::string>;
  using obj_ptr = std::unique_ptr<Object>;
  using array_ptr = std::unique_ptr<std::vector<Value>>;
  enum class Token_type {
			 object_start,
			 object_end,
			 array_start,
			 array_end,
			 colon,
			 comma,
			 str,
			 none_str,
  };

  struct Token {
    std::string text = "";
    Token_type type = Token_type::none_str;
    void clear() { text = ""; type = Token_type::none_str; };
  };

  
  class Value {
  public:
    Value(const Value& v);
    Value(Value&& v) {var = std::move(v.var);};
    Value(int x) : var(x){};
    Value(double x) : var(x){};
    Value(bool x) : var(x){};
    Value(const std::string& x) { var = std::make_unique<std::string>(x); };
    Value(const Object& obj) { var = std::make_unique<Object>(obj); };
    Value(const std::vector<Value>& arr) { var = std::make_unique<std::vector<Value>>(arr);};

    Value& operator=(const Value& v) {
      Value tv(v);
      this->var = std::move(tv.var);
      return *this;					
    }
    Value& operator=(Value&& v) {
      this->var = std::move(v.var);
      return *this;
    }
    Value& operator[](std::string_view key) { return const_cast<Value&> (*this)[key]; };
    Value& operator[](std::size_t index) { return const_cast<Value&> (*this)[index]; };
    const Value& operator[](std::string_view key) const;
    const Value& operator[](std::size_t index) const;

    int get_int() const { return std::get<int>(var); };
    double get_double() const { return std::get<double>(var); };
    bool get_bool() const { return std::get<bool>(var); };
    std::string& get_string() { return *(std::get<str_ptr>(var)); };
    const std::string& get_string() const { return *(std::get<str_ptr>(var)); };
    Object& get_object() { return *(std::get<obj_ptr>(var)); };
    const Object& get_object() const { return *(std::get<obj_ptr>(var)); };
    std::vector<Value>& get_array() { return *(std::get<array_ptr>(var)); };
    const std::vector<Value>& get_array() const { return *(std::get<array_ptr>(var)); };

    bool is_int() const { return std::holds_alternative<int>(var); };
    bool is_double() const { return std::holds_alternative<double>(var); };
    bool is_bool() const { return std::holds_alternative<bool>(var); };
    bool is_string() const { return std::holds_alternative<str_ptr>(var); };
    bool is_object() const { return std::holds_alternative<obj_ptr>(var); };
    bool is_array() const { return std::holds_alternative<array_ptr>(var); };

    friend std::ostream& operator<<(std::ostream& output, const Value& val);
  private:
    std::variant<int, double, bool, str_ptr, obj_ptr, array_ptr> var;
  };

  
  class Object {
  public:
    Object() {};
    Object(const Object& obj) : keys{obj.keys}, values{obj.values} {};
    bool has_key(std::string_view key) const { return std::find(keys.begin(), keys.end(), key) != keys.end(); }
    const Value& operator[](std::string_view key) const;
    Value& operator[](std::string_view key) { return const_cast<Object&> (*this)[key]; };
    friend Object parse_file(std::string_view filename);
    friend void print_object(Object& obj, int ind);
  private:
    void parse(const std::vector<Token>& tokens, std::vector<Token>::iterator& token_it);
    std::vector<std::string> keys;
    std::vector<Value> values;
  };

  std::vector<Token> lexer(std::string_view filename);
  Object parse_file(std::string_view filename);
  void print_object(Object& obj, int ind);
};

#endif
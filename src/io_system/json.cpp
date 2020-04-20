#include <io_system/json.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace json {
  inline bool is_token(char c) {
    return c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ':';
  }

  inline bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
  }

  inline bool is_int(std::string_view str) {
    for (auto& c : str) if(!std::isdigit(c) && c != '-') return false;
    return true;
  }

  Value::Value(const Value& v) {
    if (v.is_string()) var = std::make_unique<std::string>(v.get_string());
    else if (v.is_object()) var = std::make_unique<Object>(v.get_object());
    else if (v.is_array()) var = std::make_unique<std::vector<Value>>(v.get_array());
    else if (v.is_int()) var = v.get_int();
    else if (v.is_double()) var = v.get_double();
    else if (v.is_bool()) var = v.get_bool();
  };
  
  const Value& Value::operator[](std::string_view key) const {
    assert(is_object() && "Trying to random access Value with non-object type");
    return get_object()[key];
  }

  const Value& Value::operator[](std::size_t index) const {
    if (is_array()) return get_array()[index];
    else throw 0;
  }

  std::ostream& operator<<(std::ostream& output, const Value& val) {
    if (val.is_string()) output << val.get_string();
    else if (val.is_int()) output << val.get_int();
    else if (val.is_double()) output << val.get_double();
    else if (val.is_bool()) output << val.get_bool();
    else output << "";
    
    return output;
  }

  const Value& Object::operator[](std::string_view key) const {
    //std::cout << "Accessing object\n";
    auto it = std::find(keys.begin(), keys.end(), key);
    assert(it != keys.end() && "Object random access, wrong key");
    return values[std::distance(keys.begin(), it)];
  }


  std::vector<Token> lexer(std::string_view filename) {
    std::vector<Token> tokens;
    std::ifstream file;
    file.open(filename.data());

    Token t;
    char c;
    bool str_token = false;
    while(file.get(c)) {
      if (c == '"') {
	str_token = !str_token;
	if (str_token) t.type = Token_type::str;
      } else if (!str_token && (is_token(c) || is_whitespace(c))) {
	if (t.text.size() > 0) { tokens.push_back(t); t.clear(); }
	switch (c) {
	case '{':
	  t.text = "{";
	  t.type = Token_type::object_start;
	  break;
	case '[':
	  t.text = "[";
	  t.type = Token_type::array_start;
	  break;
	case '}':
	  t.text = "}";
	  t.type = Token_type::object_end;
	  break;
	case ']':
	  t.text = "]";
	  t.type = Token_type::array_end;
	  break;
	case ':':
	  t.text = ":";
	  t.type = Token_type::colon;
	  break;
	case ',':
	  t.text = ",";
	  t.type = Token_type::comma;
	}
	if (t.text.size() > 0) { tokens.push_back(t); t.clear(); }
      } else {
	if (c == '\\') file.get(c);
	t.text += c;
      }
    }

    return tokens;
  }

  inline void parsing_error(std::string_view token, int state) {
    std::cerr << "Parsing Error: token '" << token << "' at state: " << state << ".\n";
    std::exit(-1);
  };

  void Object::parse(const std::vector<Token>& tokens, std::vector<Token>::iterator& token_it) {
    if (token_it->type != Token_type::object_start) parsing_error(token_it->text, 0);

    std::vector<Value> array;
    Value val = 0;
    typeof(array)* target = &values;
    bool is_parsing = true;
    while(is_parsing) {
      token_it++;
      switch (token_it->type) {
      case Token_type::colon:
	keys.push_back(val.get_string());
	break;
      case Token_type::comma:
	target->push_back(val);
	break;
      case Token_type::str:
	val = token_it->text;
	break;
      case Token_type::none_str:
	if (token_it->text == "true") val = true;
	else if (token_it->text == "false") val = false;
	else if (is_int(token_it->text)) val = std::stoi(token_it->text);
	else val = static_cast<double>(std::stod(token_it->text));
	break;
      case Token_type::array_start:
	array.clear();
	target = &array;
	break;
      case Token_type::array_end:
	target->push_back(val);
	target = &values;
	val = array;
	break;
      case Token_type::object_end:
	target->push_back(val);
	is_parsing = false;
	break;
      case Token_type::object_start:
	Object rec_obj;
	rec_obj.parse(tokens, token_it); //increments token_it
	val = rec_obj;
	break;
      }
    }
  }

  Object parse_file(std::string_view filename) {
    Object obj;
    auto tokens = json::lexer(filename);
    auto iterator = tokens.begin();
    obj.parse(tokens, iterator);
    return obj;
  };

  void print_object(Object& obj, int ind = 0) {
    std::cout << std::endl << std::string(ind, ' ') << "{" << std::endl;
    std::cout << obj.keys.size() << " " << obj.values.size() << std::endl;
    for (auto key : obj.keys) {
      auto val = obj[key];
      std::cout << std::string(ind + 2, ' ') << key << ":";
      if (val.is_array()) {
	std::cout << '[';
	for (auto& v : val.get_array()) {
	  if (v.is_object()) print_object(v.get_object(), ind + 4);
	  else std::cout << v << ", ";
	}
	std::cout << std::string(ind + 2, ' ') << ']' << std::endl;
      } else if (val.is_object()) {
	print_object(val.get_object(), ind + 4);
      } else {
	std::cout<< val << std::endl;
      }
    }
    std::cout << std::string(ind, ' ') << "}\n";
  }
};

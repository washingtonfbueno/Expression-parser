#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>

class Parse {
   private:
    std::queue<std::string>* tokens;
    std::unordered_map<std::string, int> binary_priority = {
        {"**", 7},

        {"*", 6},  {"/", 6},  {"%", 6},

        {"+", 5},  {"-", 5},

        {"<", 4},  {"<=", 4}, {">", 4}, {">=", 4},

        {"==", 3}, {"!=", 3},

        {"&&", 2},

        {"||", 1},
    };

    // evaluate left and right operands within their operator
    double eval_binary(double left, double right, std::string binary_op) {
        int priority = binary_priority[binary_op];

        switch (priority) {
            case 7:
                return std::pow(left, right);

            case 6:
                if (binary_op == "*") {
                    return left * right;
                }

                if (binary_op == "/") {
                    return left / right;
                }

                if (binary_op == "%") {
                    return std::fmod(left, right);
                }

            case 5:
                if (binary_op == "+") {
                    return left + right;
                }

                if (binary_op == "-") {
                    return left - right;
                }

            case 4:
                if (binary_op == "<") {
                    return left < right;
                }

                if (binary_op == "<=") {
                    return left <= right;
                }

                if (binary_op == ">") {
                    return left > right;
                }

                if (binary_op == ">=") {
                    return left >= right;
                }

            case 3:
                if (binary_op == "==") {
                    return left == right;
                }

                if (binary_op == "!=") {
                    return left != right;
                }

            case 2:
                return left && right;

            case 1:
                return left || right;
        }

        return 0;
    }

    double eval_primary() {
        std::string token = tokens->front();

        if (token == "(") {
            tokens->pop();  // removing (
            double res =
                parse_pratt();  // result of expression inside parentheses
            tokens->pop();      // removing )
            return res;
        }

        // take number from queue and return
        tokens->pop();
        return std::stod(token);
    }

    // check if the operator is right associative, meaning we should evaluate
    // from right to left
    bool is_right_associative(std::string op) { return (op == "**"); }

    bool has_lower_priority(std::string token, std::string previous_token) {
        if (token == previous_token) {
            return !is_right_associative(token);
        }

        return binary_priority[token] <= binary_priority[previous_token];
    }

    double parse_pratt(std::string previous_token = "") {
        double left = eval_primary();

        while (!tokens->empty()) {
            std::string token = tokens->front();

            // make sure we will evaluate higher priorities operators first
            if (has_lower_priority(token, previous_token)) {
                break;
            }

            tokens->pop();
            double right = parse_pratt(token);
            left = eval_binary(left, right, token);
        }

        return left;
    }

   public:
    Parse(std::queue<std::string>* Tokens) { tokens = Tokens; }

    double result() { return parse_pratt(); }
};

int main() {
    std::queue<std::string> q({"2"});
    Parse expr = Parse(&q);
    std::cout << expr.result() << '\n';
}

#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>

class Parse {
   private:
    std::queue<std::string>* tokens;

    enum binary_operators {
        POW = 1,
        MULT,
        DIV,
        MOD,
        PLUS,
        MINUS,
        LOWER,
        LOWER_EQUAL,
        HIGHER,
        HIGHER_EQUAL,
        EQUAL,
        NOT_EQUAL,
        AND,
        OR
    };

    std::unordered_map<std::string, int> to_enum = {
        {"**", POW},   {"*", MULT},          {"/", DIV},    {"%", MOD},
        {"+", PLUS},   {"-", MINUS},         {"<", LOWER},  {"<=", LOWER_EQUAL},
        {">", HIGHER}, {">=", HIGHER_EQUAL}, {"==", EQUAL}, {"!=", NOT_EQUAL},
        {"&&", AND},   {"||", OR},
    };

    int binary_priority(std::string binary_op) {
        switch (to_enum[binary_op]) {
            case POW:
                return 7;
            case MULT:
                return 6;
            case DIV:
                return 6;
            case MOD:
                return 6;
            case PLUS:
                return 5;
            case MINUS:
                return 5;
            case LOWER:
                return 4;
            case LOWER_EQUAL:
                return 4;
            case HIGHER:
                return 4;
            case HIGHER_EQUAL:
                return 4;
            case EQUAL:
                return 3;
            case NOT_EQUAL:
                return 3;
            case AND:
                return 2;
            case OR:
                return 1;
        }

        return 0;
    }
    // evaluate left and right operands within their operator
    double eval_binary(double left, double right, std::string binary_op) {
        switch (to_enum[binary_op]) {
            case POW:
                return std::pow(left, right);
            case MULT:
                return left * right;
            case DIV:
                return left / right;
            case MOD:
                return std::fmod(left, right);
            case PLUS:
                return left + right;
            case MINUS:
                return left - right;
            case LOWER:
                return left < right;
            case LOWER_EQUAL:
                return left <= right;
            case HIGHER:
                return left > right;
            case HIGHER_EQUAL:
                return left >= right;
            case EQUAL:
                return left == right;
            case NOT_EQUAL:
                return left != right;
            case AND:
                return left && right;
            case OR:
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

        return binary_priority(token) <= binary_priority(previous_token);
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
    std::queue<std::string> q({"7", "*", "4", "+", "2"});
    Parse expr = Parse(&q);
    std::cout << expr.result() << '\n';
}

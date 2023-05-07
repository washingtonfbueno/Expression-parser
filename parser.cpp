#include <cmath>
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
        OR,

        SIN,
        COS,
        TAN,
        ARCSIN,
        ARCCOS,
        ARCTAN,
        LOG,
        LOG2,
        LOG10,
        CEIL,
        FLOOR,
        ROUND,
        TRUNC,
        ABS,
        SQRT
    };

    std::unordered_map<std::string, int> binary_to_enum = {
        {"**", POW},          {"*", MULT},         {"/", DIV},
        {"%", MOD},           {"+", PLUS},         {"-", MINUS},
        {"<", LOWER},         {"<=", LOWER_EQUAL}, {">", HIGHER},
        {">=", HIGHER_EQUAL}, {"==", EQUAL},       {"!=", NOT_EQUAL},
        {"&&", AND},          {"||", OR}};

    std::unordered_map<std::string, int> unary_to_enum = {
        {"+", PLUS},        {"-", MINUS},       {"sin", SIN},
        {"cos", COS},       {"tan", TAN},       {"arcsin", ARCSIN},
        {"arccos", ARCCOS}, {"arctan", ARCTAN}, {"log", LOG},
        {"log2", LOG2},     {"log10", LOG10},   {"ceil", CEIL},
        {"floor", FLOOR},   {"round", ROUND},   {"trunc", TRUNC},
        {"abs", ABS},       {"sqrt", SQRT}};

    int op_priority(std::string op) {
        switch (binary_to_enum[op]) {
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
        switch (binary_to_enum[binary_op]) {
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

    double eval_unary(double right, std::string unary_op) {
        switch (unary_to_enum[unary_op]) {
            case MINUS:
                return -right;
            case PLUS:
                return right;
            case SIN:
                return std::sin(right * 3.14159265 / 180);
            case COS:
                return std::cos(right * 3.14159265 / 180);
            case TAN:
                return std::tan(right * 3.14159265 / 180);
            case ARCSIN:
                return std::asin(right) * 180 / 3.14159265;
            case ARCCOS:
                return std::acos(right) * 180 / 3.14159265;
            case ARCTAN:
                return std::atan(right) * 180 / 3.14159265;
            case LOG:
                return std::log(right);
            case LOG2:
                return std::log2(right);
            case LOG10:
                return std::log10(right);
            case CEIL:
                return std::ceil(right);
            case FLOOR:
                return std::floor(right);
            case ROUND:
                return std::round(right);
            case TRUNC:
                return std::trunc(right);
            case ABS:
                return std::abs(right);
            case SQRT:
                return std::sqrt(right);
        }

        return 0;
    }

    // check if the operator is right associative, meaning we should evaluate
    // from right to left
    bool is_right_associative(std::string op) {
        if (op == "**") {
            return true;
        }

        return false;
    }

    bool is_unary(std::string token) {
        if (unary_to_enum.count(token)) {
            return true;
        }

        return false;
    }

    bool has_lower_priority(std::string token, std::string previous_token) {
        if (token == previous_token) {
            return !is_right_associative(token);
        }

        return op_priority(token) <= op_priority(previous_token);
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
    double parse_pratt(std::string previous_token = "") {
        double left{};

        if (is_unary(tokens->front())) {
            std::string unary_op = tokens->front();
            tokens->pop();
            double right = parse_pratt(tokens->front());
            left = eval_unary(right, unary_op);
        } else {
            left = eval_primary();
        }

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
    std::queue<std::string> q({"sin", "0.5", "+", "2"});
    Parse expr = Parse(&q);
    std::cout << expr.result() << '\n';
}

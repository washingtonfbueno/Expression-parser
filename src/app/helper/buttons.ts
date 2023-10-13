import {
    binaryOperators,
    unaryBinaryOperators,
    unaryOperators,
} from "./pratt-parser/lexer";

export const buttons = binaryOperators
    .concat(unaryBinaryOperators)
    .concat(unaryOperators);

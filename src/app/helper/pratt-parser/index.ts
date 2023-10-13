import { Lexer } from "./lexer";
import { Output } from "./output";
import { Parser } from "./parser";

export const evaluateExpression = (expressionInput: string) => {
    const lexer = new Lexer(expressionInput);
    const tokens = lexer.getTokens();

    //const allTokensValid = lexer.allTokensValid();

    const prattParser = new Parser(tokens);

    try {
        const result = prattParser.startParse();
        console.log(result);
    } catch (e: any) {
        console.log(e.message);
    }

    /* if (!allTokensValid) {
        return new Output(tokens, allTokensValid);
    }

    return new Output(tokens, allTokensValid); */
};

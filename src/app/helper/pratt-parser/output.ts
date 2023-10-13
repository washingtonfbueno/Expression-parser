import { Token } from "./token";

export class Output {
    private tokens: Token[];
    private allTokensValid: boolean;

    constructor(tokens: Token[], allTokensValid: boolean) {
        this.tokens = tokens;
        this.allTokensValid = allTokensValid;
    }

    getOutput() {
        if (!this.allTokensValid) {
            return { type: "invalid-token", tokens: this.tokens };
        }

        return { type: "success", tokens: this.tokens };
    }
}

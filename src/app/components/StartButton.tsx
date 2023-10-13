import { NextPage } from "next";
import { InputContext } from "../contexts/InputContext";
import { useContext } from "react";
import { evaluateExpression } from "../helper/pratt-parser";

interface Props {}

export const StartButton: NextPage<Props> = (props) => {
    const { expressionInput, setExpressionInput } = useContext(InputContext)!;

    return (
        <button
            onClick={() => {
                evaluateExpression(expressionInput);
            }}
            className="p-2 w-[4rem] h-[4rem] aspect-square rounded-lg text-center text-xl bg-blue-400 hover:bg-blue-200 text-white"
        >
            ▷
        </button>
    );
};

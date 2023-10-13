import { NextPage } from "next";
import { useContext } from "react";
import { InputContext } from "../contexts/InputContext";

interface Props {
    button: string;
}

export const Button: NextPage<Props> = (props) => {
    const { expressionInput, setExpressionInput } = useContext(InputContext)!;
    const { button } = props;

    return (
        <button
            onClick={() => setExpressionInput(expressionInput + button)}
            className="rounded-md p-2 bg-blue-400 hover:bg-blue-200 text-white"
        >
            {button}
        </button>
    );
};

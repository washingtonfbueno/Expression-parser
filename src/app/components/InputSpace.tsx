import { useContext } from "react";
import { InputContext } from "../contexts/InputContext";

export const InputSpace = () => {
    const { expressionInput, setExpressionInput } = useContext(InputContext)!;
    return (
        <textarea
            onChange={(event) => setExpressionInput(event.target.value)}
            value={expressionInput}
            className="flex-grow border-blue-400 border-2 border-dashed rounded-sm px-6 py-1 focus:outline-none resize-none"
        />
    );
};

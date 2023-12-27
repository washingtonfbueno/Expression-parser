import { NextPage } from "next";
import {
    createContext,
    useState,
    ReactNode,
    Dispatch,
    SetStateAction,
} from "react";

interface ContextData {
    expressionInput: string;
    setExpressionInput: Dispatch<SetStateAction<string>>;
    expressionOutput: string[];
    setExpressionOutput: Dispatch<SetStateAction<string[]>>;
}

interface Props {
    children: ReactNode;
}

export const InputContext = createContext<ContextData | undefined>(undefined);

export const InputContextProvider: NextPage<Props> = ({ children }) => {
    const [expressionInput, setExpressionInput] = useState<string>("");
    const [expressionOutput, setExpressionOutput] = useState<string[]>([]);

    return (
        <InputContext.Provider
            value={{
                expressionInput,
                setExpressionInput,
                expressionOutput,
                setExpressionOutput,
            }}
        >
            {children}
        </InputContext.Provider>
    );
};

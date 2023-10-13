import { useContext } from "react";
import { InputContext } from "../contexts/InputContext";

export const OutputSpace = () => {
    const {} = useContext(InputContext)!;
    return (
        <div className="flex border-blue-400 border-2 rounded-sm px-6 py-1 h-[8rem] overflow-auto">
            1 + 5
        </div>
    );
};

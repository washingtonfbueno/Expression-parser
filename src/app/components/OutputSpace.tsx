import { useContext, useEffect, useRef } from "react";
import { InputContext } from "../contexts/InputContext";

export const OutputSpace = () => {
    const { expressionOutput } = useContext(InputContext)!;
    const outputSpaceRef: React.RefObject<HTMLDivElement> =
        useRef<HTMLDivElement>(null)!;

    useEffect(() => {
        // Always scroll to bottom
        outputSpaceRef.current!.scrollTop =
            outputSpaceRef.current!.scrollHeight;
    }, [expressionOutput]);

    return (
        <div
            ref={outputSpaceRef}
            className="flex flex-col border-blue-400 border-2 rounded-sm pl-4 pr-6 py-2 h-[8rem] overflow-auto"
        >
            {expressionOutput.map((output, index) => (
                <div key={index}>
                    {">"} {output}
                </div>
            ))}
        </div>
    );
};

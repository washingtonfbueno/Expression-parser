"use client";

import { InputContextProvider } from "./contexts/InputContext";
import { Buttons } from "./components/Buttons";
import { InputSpace } from "./components/InputSpace";
import { StartButton } from "./components/StartButton";
import { OutputSpace } from "./components/OutputSpace";

export default function Home() {
    return (
        <InputContextProvider>
            <div className="flex justify-center">
                <div className="flex flex-col justify-center px-12 space-y-6 max-w-[720px] w-[100%] h-screen">
                    <div className="flex items-center space-x-4 py-4">
                        <InputSpace />
                        <StartButton />
                    </div>

                    <OutputSpace />

                    <Buttons />
                </div>
            </div>
        </InputContextProvider>
    );
}

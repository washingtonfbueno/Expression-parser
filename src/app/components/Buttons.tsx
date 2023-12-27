import { buttons } from "../helper/buttons";
import { Button } from "./Button";

export const Buttons = () => {
    return (
        <div className="grid grid-cols-4 gap-2">
            {buttons.map((button, index) => (
                <Button button={button} key={index} />
            ))}
        </div>
    );
};

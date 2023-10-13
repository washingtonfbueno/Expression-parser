export const Speed = () => {
    const speeds = [1, 1 / 2, 1 / 4, 1 / 8, 1 / 16];

    return (
        <div className="self-end space-x-4">
            <span>Speed</span>
            <select
                name="cars"
                id="cars"
                form="carform"
                className="border-blue-400 border-2 focus:outline-none w-24 border-dashed text-center"
            >
                {speeds.map((val, index) => (
                    <option key={index} value={val}>
                        {val * 100}%
                    </option>
                ))}
            </select>
        </div>
    );
};

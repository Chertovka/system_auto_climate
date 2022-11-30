document.addEventListener("DOMContentLoaded", () => {
    const DURATION_TIMEOUT = 5000;

    const config = {
        intensity: {
            min: 997.67,
            max: 998.12
        },
        temperature: {
            min: 20.13,
            max: 20.56
        },
        pressure: {
            min: 763.68,
            max: 766.89
        },
        humidity: {
            min: 51.41,
            max: 51.68
        }
    }

    const outputList = document.querySelectorAll("[data-type='output']");

    const getRandomInt = ({min, max}) => (Math.random() * (max - min) + min).toFixed(2);

    const printNumbers = () => {
        setInterval(() => {
            outputList.forEach((output) => {
                const outputID = output.id;

                if (!Object.keys(config).includes(outputID)) {
                    return;
                }

                output.textContent = getRandomInt(config[outputID]);
            });
         }, DURATION_TIMEOUT);
    }

    printNumbers();
});
(function(document) {
    "use strict";

    var output = document.querySelector("time"),
        counterId = null,
        start = null;

    function pad(value) {
        if (value < 0) {
            return "00";
        }

        return value < 10 ? "0" + value : value.toString();
    }

    function displayTime(value) {
        var onlySeconds,
            seconds,
            onlyMinutes,
            minutes;

        value = value - start;

        onlySeconds = Math.round(value / 1000);
        seconds = onlySeconds % 60;
        onlyMinutes = Math.round(onlySeconds / 60);
        minutes = onlyMinutes % 60;

        return pad(minutes) + ":" + pad(seconds);
    }

    function print() {
        output.innerText = displayTime(Date.now());
    }

    function counter() {
        start = Date.now();
        output.innerText = "00:00";

        if (counterId) {
            clearInterval(counterId);
        }

        counterId = setInterval(print, 1000);
    }

    document.querySelector("button").addEventListener("click", counter);

} (window.document));
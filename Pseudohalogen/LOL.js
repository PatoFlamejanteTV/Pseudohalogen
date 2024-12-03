// yes, my malware uses HTML + JS TOO
// Simple code that makes an prompt() windows and send its value to "what"

// and it also uses "what" to manipulate DOM (HTML, basically)

window.onload = function() {
    var what = prompt("Whos your savior?")
    alert("Seems that " + what + " cannot save you now!")
    document.write(`
        <h1>${what}?</h1><hr><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p><br>
        <p>Seems that ${what} cannot save you now!</p>
    `)
    };
const correctAwnser = 4
const correctSubmit = "Lorem ipsum"
let blockAwnser = false
let blockSubmit = false

const awnser = []
for (let i = 0; i < 5; i++) {
    awnser[i] = document.querySelector(`.a${i + 1}`)
    awnser[i].addEventListener('click', function () {
        if (!blockAwnser) {
            let msg = document.querySelector('.msg1')
            let paragrafo = document.createElement("p");
            let quebra = document.createElement("br");
            msg.appendChild(quebra)
            if (i + 1 == correctAwnser) {
                awnser[i].classList.remove("btn-outline-primary");
                awnser[i].classList.add("btn-success");
                paragrafo.textContent = 'CORRECT AWNSER'
            }
            else {
                awnser[i].classList.remove("btn-outline-primary");
                awnser[i].classList.add("btn-danger");
                paragrafo.textContent = 'INCORRECT AWNSER'
            }
            msg.appendChild(paragrafo)
            blockAwnser = true
        }

    })
}

submit = document.querySelector(`.submit`)
submit.addEventListener('click', function () {
    form = document.querySelector(`.form`)
    if (!blockSubmit) {
        let msg = document.querySelector('.msg2')
        let paragrafo = document.createElement("p");
        let quebra = document.createElement("br");
        msg.appendChild(quebra)
        if (correctSubmit.toUpperCase() == form.value.toUpperCase()) {
            submit.classList.remove("btn-outline-primary");
            submit.classList.add("btn-success");
            paragrafo.textContent = 'CORRECT AWNSER'
        }
        else {
            submit.classList.remove("btn-outline-primary");
            submit.classList.add("btn-danger");
            paragrafo.textContent = 'INCORRECT AWNSER'
        }
        msg.appendChild(paragrafo)
        blockSubmit = true
    }
})

const dark = document.querySelector('.dark-mode')

let biscoito = document.cookie
if (biscoito == 'darkmode=on')
{
    changeColor()
}

function changeColor()
{
    const fundo = document.querySelector('body')
    console.log(fundo.style.backgroundColor)
    if (fundo.style.backgroundColor == '' || fundo.style.backgroundColor == 'white'){
        fundo.style.backgroundColor = '#181d20'
        fundo.style.color = 'white'
        document.cookie = 'darkmode = on';
    }
    else {
        fundo.style.backgroundColor = 'white'
        fundo.style.color = 'black'
        document.cookie = 'darkmode = off';
    }
    
}

dark.addEventListener("click", changeColor)
package SistemaBiblioteca.src.frontend.comandos;

import SistemaBiblioteca.src.frontend.Biblioteca;

public class RegistrarObservador implements Comando {

    @Override
    public Object executar(int ... params) throws IllegalArgumentException{
        if (params.length < 2) {
            throw new IllegalArgumentException("O comando deve receber dois parâmetros: ID do usuário e ID do livro.");
        }
        
        Biblioteca biblioteca = Biblioteca.obterInstancia();
        biblioteca.registrarObservador(params[0], params[1]);

        System.out.println("Registro de observador realizado com sucesso.");
        return true;
    }
}


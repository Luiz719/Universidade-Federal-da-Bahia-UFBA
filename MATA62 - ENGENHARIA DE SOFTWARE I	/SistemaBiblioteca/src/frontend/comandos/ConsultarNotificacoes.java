package SistemaBiblioteca.src.frontend.comandos;

import SistemaBiblioteca.src.frontend.Biblioteca;

public class ConsultarNotificacoes implements Comando {

    @Override
    public Object executar(int ... params) throws IllegalArgumentException {
        if (params.length < 1) {
            throw new IllegalArgumentException("O comando deve receber o seguinte parâmetro: ID do usuário.");
        }
        
        int n = Biblioteca.obterInstancia().consultarNotificacoes(params[0]);
        System.out.println("Total de " + n + " notificações.");

        return true;
    }
}


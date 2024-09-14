package SistemaBiblioteca.src.frontend.comandos;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;
import SistemaBiblioteca.src.frontend.Biblioteca;

public class RealizarEmprestimo implements Comando {

    @Override
    public Object executar(int ... params) throws IllegalArgumentException {
        if (params.length < 2) {
            throw new IllegalArgumentException("O comando deve receber dois parâmetros: ID do usuário e ID do livro.");
        }
        Biblioteca biblioteca = Biblioteca.obterInstancia();
        boolean sucesso = biblioteca.realizarEmprestimo(params[0], params[1]);

        Usuario usuario = biblioteca.consultarUsuario(params[0]);        
        Livro livro = biblioteca.consultarLivro(params[1]);
        
        if (sucesso) {
            System.out.println("O usuário " + usuario.getNome() + " realizou um empréstimo do livro \"" + livro.getTitulo() + "\" com sucesso.");
        }
        return sucesso;
    }
}


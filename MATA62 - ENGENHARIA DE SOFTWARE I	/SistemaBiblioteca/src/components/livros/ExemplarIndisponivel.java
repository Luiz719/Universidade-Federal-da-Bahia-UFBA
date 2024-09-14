package SistemaBiblioteca.src.components.livros;

import SistemaBiblioteca.src.components.Mensagem;

public class ExemplarIndisponivel implements EstadoLivro {

    @Override
    public boolean podeSerEmprestado(Livro livro) {
        Mensagem.exemplarIndisponivel();
        return false;
    }
    
}

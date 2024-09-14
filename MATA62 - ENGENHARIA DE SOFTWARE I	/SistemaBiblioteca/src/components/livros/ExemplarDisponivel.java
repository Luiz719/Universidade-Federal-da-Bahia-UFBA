package SistemaBiblioteca.src.components.livros;

import SistemaBiblioteca.src.components.Mensagem;

public class ExemplarDisponivel implements EstadoLivro{

    @Override
    public boolean podeSerEmprestado(Livro livro) {
        if(livro.getNumeroExemplaresDisponiveis() == 0){
            Mensagem.exemplarIndisponivel();
            return false;
        }
        return true;
    }
    
}

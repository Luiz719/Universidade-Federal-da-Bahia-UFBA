package SistemaBiblioteca.src.components.livros;

import SistemaBiblioteca.src.components.Emprestimo;

public class LivroExemplar {
    private Livro livro;
    private int codExemplar;
    private StatusExemplar status;
    private Emprestimo emprestimo;

    public LivroExemplar(Livro livro, int codEx){
        this.livro = livro;
        this.codExemplar = codEx;
        this.status = StatusExemplar.Disponivel;
        this.emprestimo = null;
    }

    public int getCodExemplar(){
        return codExemplar;
    }
    
    public void emprestar(Emprestimo novoEmprestimo){
        this.status = StatusExemplar.Emprestado;
        this.emprestimo = novoEmprestimo;
    }

    public void devolver(){
        this.status = StatusExemplar.Disponivel;
        this.emprestimo = null;
    }

    public int getCodLivro(){
        return livro.getId();
    }

    public StatusExemplar getStatus(){
        return status;
    }

    public Emprestimo getEmprestimo(){
        return emprestimo;
    }
}

package SistemaBiblioteca.src.components;

import java.time.LocalDateTime;

import SistemaBiblioteca.src.components.livros.LivroExemplar;
import SistemaBiblioteca.src.components.usuarios.Usuario;

public class Emprestimo {
    private Usuario solicitante;
    private LivroExemplar exemplar;
    private LocalDateTime dataEmprestimo;
    private LocalDateTime dataDevolucao;
    private LocalDateTime dataFinalizado;
    private boolean finalizado;

    public Emprestimo(Usuario solicitante, LivroExemplar exemplar) {
        this.solicitante = solicitante;
        this.exemplar = exemplar;
        this.dataEmprestimo = LocalDateTime.now();
        this.dataDevolucao = dataEmprestimo.plusDays(solicitante.getTempoEmprestimo());
        this.finalizado = false;
    }

    public Usuario getSolicitante(){
        return solicitante;
    }
    
    public int getCodExemplar(){
        return exemplar.getCodExemplar();
    }

    public int getCodLivro(){
        return exemplar.getCodLivro();
    }

    public LocalDateTime getDataDevolucao(){
        return dataDevolucao;
    }

    public LocalDateTime getDataFinalizado(){
        return this.dataFinalizado;
    }

    public LocalDateTime getDataEmprestimo(){
        return this.dataEmprestimo;
    }

    public boolean estarAtrasado(){
        LocalDateTime dataAtual = LocalDateTime.now();
        return this.getDataDevolucao().isBefore(dataAtual);     
    }

    public boolean estaFinalizado() {
        return this.finalizado;
    }

    public void finalizar() {
        if (!this.finalizado) {
            this.dataFinalizado = LocalDateTime.now();
            this.finalizado = true;
        }
    }
}

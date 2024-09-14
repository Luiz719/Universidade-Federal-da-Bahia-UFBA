package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.VerificadorProfessor;

public class Professor extends Usuario implements ObservadorReserva{
    private int qntNotificacoes = 0;

    public Professor(int id, String nome){
        this.setId(id);
        this.setNome(nome);
        this.setTempoEmprestimo(7);
        this.setLimiteEmprestimo(9999);
        this.setVerificador(new VerificadorProfessor());
        this.setEstadoDevedor(new NaoDevedor());
        this.setEstadoEmprestimo(new EmprestimoPossivel());
        this.setEstadoReserva(new ReservaPossivel());   
    }

    @Override
    public boolean podeEmprestar() {
        return this.getEstadoDevedor().podeEmprestar(this) && 
                this.getEstadoEmprestimo().podeEmprestar(this);
    }

    public void atualiza() {
        qntNotificacoes++;
    }

    public int getQntNotificacoes() {
        return qntNotificacoes;
    }
}

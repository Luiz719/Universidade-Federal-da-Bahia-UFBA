package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.VerificadorGrad;

public class Grad extends Usuario{

    public Grad(int id, String nome){
        this.setId(id);
        this.setNome(nome);
        this.setTempoEmprestimo(3);
        this.setLimiteEmprestimo(3);
        this.setVerificador(new VerificadorGrad());
        this.setEstadoDevedor(new NaoDevedor());
        this.setEstadoEmprestimo(new EmprestimoPossivel());
        this.setEstadoReserva(new ReservaPossivel());   
    }

    @Override
    public boolean podeEmprestar() {
        return this.getEstadoDevedor().podeEmprestar(this) && 
                this.getEstadoEmprestimo().podeEmprestar(this);
    }
}

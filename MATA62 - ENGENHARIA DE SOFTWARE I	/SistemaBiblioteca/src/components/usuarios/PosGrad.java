package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.VerificadorPosGrad;

public class PosGrad extends Usuario{

    public PosGrad(int id, String nome){
        this.setId(id);
        this.setNome(nome);
        this.setTempoEmprestimo(4);
        this.setLimiteEmprestimo(4);
        this.setVerificador(new VerificadorPosGrad());
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

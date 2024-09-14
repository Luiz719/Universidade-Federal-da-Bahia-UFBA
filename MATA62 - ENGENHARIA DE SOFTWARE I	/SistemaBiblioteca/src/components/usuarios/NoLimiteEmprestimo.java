package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.Mensagem;

public class NoLimiteEmprestimo implements EstadoUsuarioEmprestimo {

    @Override
    public boolean podeEmprestar(Usuario usuario) {
        Mensagem.noLimiteEmprestimo();
        return false;
    }
    
}

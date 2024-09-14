package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.Mensagem;

public class Devedor implements EstadoUsuarioEmprestimo {

    @Override
    public boolean podeEmprestar(Usuario usuario) {
        Mensagem.usuarioDevedor();
        return false;
    }
    
}

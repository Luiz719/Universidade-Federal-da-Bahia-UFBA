package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.Mensagem;

public class NaoDevedor implements EstadoUsuarioEmprestimo{

    @Override
    public boolean podeEmprestar(Usuario usuario) {
        boolean result = usuario.temEmprestimoAtrasado();
        if(result){
            Mensagem.usuarioDevedor();
            return false;
        }
        return true;
    }
    
}

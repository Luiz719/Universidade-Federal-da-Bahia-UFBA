package SistemaBiblioteca.src.components.usuarios;

import SistemaBiblioteca.src.components.Mensagem;

public class NoLimiteReserva implements EstadoUsuarioReserva{

    @Override
    public boolean podeReservar(Usuario usuario) {
        Mensagem.noLimiteReserva();
        return false;
    }
    
}

package SistemaBiblioteca.src.components.usuarios;

public class ReservaPossivel implements EstadoUsuarioReserva {

    @Override
    public boolean podeReservar(Usuario usuario) {
        
        return true;
    }
    
}

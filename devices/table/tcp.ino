using tbl = shs::TableAPI; 

void TCPhandle(shs::DTPdata& stc) {

  switch (stc.data->readPtr[0]) {
    case tbl::braR:
      {
     //   setBraR(stc.data->readPtr[1]);
      }
      break;
    case tbl::braL:
      {
      //  setBraL(stc.data->readPtr[1]);
      }
      break;
    case tbl::bra:
      {
       // setBra(stc.data->readPtr[1]);
      }
      break;

    case tbl::bulb:
      {
        digitalWrite(BULBpin, stc.data->readPtr[1]);
      }
      break;

    case tbl::update:
    {
      shs::_update_ID = IP[3];
      shs::updateRun();
    }
  }
}

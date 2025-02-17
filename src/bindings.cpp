#include <emscripten/bind.h>
#include "intern/drw_dbg.h"
#include "drw_base.h"
#include "drw_entities.h"
#include "drw_header.h"
#include "libdxfrw.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(DRW_base) {
  enum_<DRW::Version>("Version")
    .value("UNKNOWNV", DRW::UNKNOWNV)
    .value("AC1006", DRW::AC1006)
    .value("AC1009", DRW::AC1009)
    .value("AC1012", DRW::AC1012)
    .value("AC1014", DRW::AC1014)
    .value("AC1015", DRW::AC1015)
    .value("AC1018", DRW::AC1018)
    .value("AC1021", DRW::AC1021)
    .value("AC1024", DRW::AC1024)
    .value("AC1027", DRW::AC1027);

  enum_<DRW::error>("Error")
    .value("BAD_NONE", DRW::BAD_NONE)
    .value("BAD_UNKNOWN", DRW::BAD_UNKNOWN)
    .value("BAD_OPEN", DRW::BAD_OPEN)
    .value("BAD_VERSION", DRW::BAD_VERSION)
    .value("BAD_READ_METADATA", DRW::BAD_READ_METADATA)
    .value("BAD_READ_FILE_HEADER", DRW::BAD_READ_FILE_HEADER)
    .value("BAD_READ_HEADER", DRW::BAD_READ_HEADER)
    .value("BAD_READ_HANDLES", DRW::BAD_READ_HANDLES)
    .value("BAD_READ_CLASSES", DRW::BAD_READ_CLASSES)
    .value("BAD_READ_TABLES", DRW::BAD_READ_TABLES)
    .value("BAD_READ_BLOCKS", DRW::BAD_READ_BLOCKS)
    .value("BAD_READ_ENTITIES", DRW::BAD_READ_ENTITIES)
    .value("BAD_READ_OBJECTS", DRW::BAD_READ_OBJECTS);

  enum_<DRW::DBG_LEVEL>("DBG_LEVEL")
    .value("NONE", DRW::NONE)
    .value("DEBUG", DRW::DEBUG);

  enum_<DRW::ColorCodes>("ColorCodes")
    .value("ColorByLayer", DRW::ColorByLayer)
    .value("ColorByBlock", DRW::ColorByBlock);

  enum_<DRW::Space>("Space")
    .value("ModelSpace", DRW::ModelSpace)
    .value("PaperSpace", DRW::PaperSpace);

  enum_<DRW::HandleCodes>("HandleCodes")
    .value("NoHandle", DRW::NoHandle);

  enum_<DRW::ShadowMode>("ShadowMode")
    .value("CastAndReceieveShadows", DRW::CastAndReceieveShadows)
    .value("CastShadows", DRW::CastShadows)
    .value("ReceiveShadows", DRW::ReceiveShadows)
    .value("IgnoreShadows", DRW::IgnoreShadows);

  enum_<DRW::MaterialCodes>("MaterialCodes")
    .value("MaterialByLayer", DRW::MaterialByLayer);

  enum_<DRW::PlotStyleCodes>("PlotStyleCodes")
    .value("DefaultPlotStyle", DRW::DefaultPlotStyle);

  enum_<DRW::TransparencyCodes>("TransparencyCodes")
    .value("Opaque", DRW::Opaque)
    .value("Transparent", DRW::Transparent);

  class_<DRW_Coord>("DRW_Coord")
    .constructor<>()
    .constructor<double, double, double>()
    .function("unitize", &DRW_Coord::unitize)
    .property("x", &DRW_Coord::x)
    .property("y", &DRW_Coord::y)
    .property("z", &DRW_Coord::z);

  class_<DRW_Vertex2D>("DRW_Vertex2D")
    .constructor<>()
    .constructor<double, double, double>()
    .property("x", &DRW_Vertex2D::x)
    .property("y", &DRW_Vertex2D::y)
    .property("stawidth", &DRW_Vertex2D::stawidth)
    .property("endwidth", &DRW_Vertex2D::endwidth)
    .property("bulge", &DRW_Vertex2D::bulge);

  enum_<DRW_Variant::TYPE>("DRW_VariantType")
    .value("STRING", DRW_Variant::STRING)
    .value("INTEGER", DRW_Variant::INTEGER)
    .value("DOUBLE", DRW_Variant::DOUBLE)
    .value("COORD", DRW_Variant::COORD)
    .value("INVALID", DRW_Variant::INVALID);

  class_<DRW_Variant>("DRW_Variant")
    .constructor<>()
    .constructor<int, dint32>()
    .constructor<int, duint32>()
    .constructor<int, double>()
    .constructor<int, UTF8STRING>()
    .constructor<int, DRW_Coord>()
    .function("addString", &DRW_Variant::addString)
    .function("addInt", &DRW_Variant::addInt)
    .function("addDouble", &DRW_Variant::addDouble)
    .function("addCoord", &DRW_Variant::addCoord)
    .function("setCoordX", &DRW_Variant::setCoordX)
    .function("setCoordY", &DRW_Variant::setCoordY)
    .function("setCoordZ", &DRW_Variant::setCoordZ)
    .function("type", &DRW_Variant::type)
    .function("code", &DRW_Variant::code);

  class_<dwgHandle>("dwgHandle")
    .constructor<>()
    .property("code", &dwgHandle::code)
    .property("size", &dwgHandle::size)
    .property("ref", &dwgHandle::ref);

  enum_<DRW_LW_Conv::lineWidth>("LineWidth")
    .value("width00", DRW_LW_Conv::width00)
    .value("width01", DRW_LW_Conv::width01)
    .value("width02", DRW_LW_Conv::width02)
    .value("width03", DRW_LW_Conv::width03)
    .value("width04", DRW_LW_Conv::width04)
    .value("width05", DRW_LW_Conv::width05)
    .value("width06", DRW_LW_Conv::width06)
    .value("width07", DRW_LW_Conv::width07)
    .value("width08", DRW_LW_Conv::width08)
    .value("width09", DRW_LW_Conv::width09)
    .value("width10", DRW_LW_Conv::width10)
    .value("width11", DRW_LW_Conv::width11)
    .value("width12", DRW_LW_Conv::width12)
    .value("width13", DRW_LW_Conv::width13)
    .value("width14", DRW_LW_Conv::width14)
    .value("width15", DRW_LW_Conv::width15)
    .value("width16", DRW_LW_Conv::width16)
    .value("width17", DRW_LW_Conv::width17)
    .value("width18", DRW_LW_Conv::width18)
    .value("width19", DRW_LW_Conv::width19)
    .value("width20", DRW_LW_Conv::width20)
    .value("width21", DRW_LW_Conv::width21)
    .value("width22", DRW_LW_Conv::width22)
    .value("width23", DRW_LW_Conv::width23)
    .value("widthByLayer", DRW_LW_Conv::widthByLayer)
    .value("widthByBlock", DRW_LW_Conv::widthByBlock)
    .value("widthDefault", DRW_LW_Conv::widthDefault);

  class_<DRW_LW_Conv>("DRW_LW_Conv")
    .class_function("lineWidth2dxfInt", &DRW_LW_Conv::lineWidth2dxfInt)
    .class_function("lineWidth2dwgInt", &DRW_LW_Conv::lineWidth2dwgInt)
    .class_function("dxfInt2lineWidth", &DRW_LW_Conv::dxfInt2lineWidth)
    .class_function("dwgInt2lineWidth", &DRW_LW_Conv::dwgInt2lineWidth);
}

EMSCRIPTEN_BINDINGS(DRW_dbg) {
  enum_<DRW_dbg::LEVEL>("LEVEL")
    .value("NONE", DRW_dbg::NONE)
    .value("DEBUG", DRW_dbg::DEBUG);

  class_<DRW_dbg>("DRW_dbg")
    .class_function("getInstance", &DRW_dbg::getInstance, allow_raw_pointer<DRW_dbg*>())
    .function("setLevel", &DRW_dbg::setLevel)
    .function("getLevel", &DRW_dbg::getLevel)
    .function("printString", select_overload<void(const std::string)>(&DRW_dbg::print))
    .function("printInt", select_overload<void(int)>(&DRW_dbg::print))
    .function("printUnsignedInt", select_overload<void(unsigned int)>(&DRW_dbg::print))
    .function("printLongLongInt", select_overload<void(long long int)>(&DRW_dbg::print))
    .function("printLongUnsignedInt", select_overload<void(long unsigned int)>(&DRW_dbg::print))
    .function("printLongLongUnsignedInt", select_overload<void(long long unsigned int)>(&DRW_dbg::print))
    .function("printDouble", select_overload<void(double)>(&DRW_dbg::print))
    .function("printH", &DRW_dbg::printH)
    .function("printB", &DRW_dbg::printB)
    .function("printHL", &DRW_dbg::printHL)
    .function("printPT", &DRW_dbg::printPT);
}

EMSCRIPTEN_BINDINGS(DRW_Header) {
  class_<DRW_Header>("DRW_Header")
    .constructor<>()
    .function("addDouble", &DRW_Header::addDouble)
    .function("addInt", &DRW_Header::addInt)
    .function("addStr", &DRW_Header::addStr)
    .function("addCoord", &DRW_Header::addCoord)
    .function("getComments", &DRW_Header::getComments)
    .function("write", &DRW_Header::write, allow_raw_pointer<dxfWriter*>())
    .function("addComment", &DRW_Header::addComment)
    .property("vars", &DRW_Header::vars);
}

EMSCRIPTEN_BINDINGS(DRW_Objects) {
  enum_<DRW::TTYPE>("TTYPE")
    .value("UNKNOWNT", DRW::UNKNOWNT)
    .value("LTYPE", DRW::LTYPE)
    .value("LAYER", DRW::LAYER)
    .value("STYLE", DRW::STYLE)
    .value("DIMSTYLE", DRW::DIMSTYLE)
    .value("VPORT", DRW::VPORT)
    .value("BLOCK_RECORD", DRW::BLOCK_RECORD)
    .value("APPID", DRW::APPID)
    .value("IMAGEDEF", DRW::IMAGEDEF);

  class_<DRW_TableEntry>("DRW_TableEntry")
    .constructor<>()
    .property("tType", &DRW_TableEntry::tType)
    .property("handle", &DRW_TableEntry::handle)
    .property("parentHandle", &DRW_TableEntry::parentHandle)
    .property("name", &DRW_TableEntry::name)
    .property("flags", &DRW_TableEntry::flags)
    .property("extData", &DRW_TableEntry::extData);

  class_<DRW_Dimstyle, base<DRW_TableEntry>>("DRW_Dimstyle")
    .constructor<>()
    .function("reset", &DRW_Dimstyle::reset)
    .property("dimpost", &DRW_Dimstyle::dimpost)
    .property("dimapost", &DRW_Dimstyle::dimapost)
    .property("dimblk", &DRW_Dimstyle::dimblk)
    .property("dimblk1", &DRW_Dimstyle::dimblk1)
    .property("dimblk2", &DRW_Dimstyle::dimblk2)
    .property("dimscale", &DRW_Dimstyle::dimscale)
    .property("dimasz", &DRW_Dimstyle::dimasz)
    .property("dimexo", &DRW_Dimstyle::dimexo)
    .property("dimdli", &DRW_Dimstyle::dimdli)
    .property("dimexe", &DRW_Dimstyle::dimexe)
    .property("dimrnd", &DRW_Dimstyle::dimrnd)
    .property("dimdle", &DRW_Dimstyle::dimdle)
    .property("dimtp", &DRW_Dimstyle::dimtp)
    .property("dimtm", &DRW_Dimstyle::dimtm)
    .property("dimfxl", &DRW_Dimstyle::dimfxl)
    .property("dimtxt", &DRW_Dimstyle::dimtxt)
    .property("dimcen", &DRW_Dimstyle::dimcen)
    .property("dimtsz", &DRW_Dimstyle::dimtsz)
    .property("dimaltf", &DRW_Dimstyle::dimaltf)
    .property("dimlfac", &DRW_Dimstyle::dimlfac)
    .property("dimtvp", &DRW_Dimstyle::dimtvp)
    .property("dimtfac", &DRW_Dimstyle::dimtfac)
    .property("dimgap", &DRW_Dimstyle::dimgap)
    .property("dimaltrnd", &DRW_Dimstyle::dimaltrnd)
    .property("dimtol", &DRW_Dimstyle::dimtol)
    .property("dimlim", &DRW_Dimstyle::dimlim)
    .property("dimtih", &DRW_Dimstyle::dimtih)
    .property("dimtoh", &DRW_Dimstyle::dimtoh)
    .property("dimse1", &DRW_Dimstyle::dimse1)
    .property("dimse2", &DRW_Dimstyle::dimse2)
    .property("dimtad", &DRW_Dimstyle::dimtad)
    .property("dimzin", &DRW_Dimstyle::dimzin)
    .property("dimazin", &DRW_Dimstyle::dimazin)
    .property("dimalt", &DRW_Dimstyle::dimalt)
    .property("dimaltd", &DRW_Dimstyle::dimaltd)
    .property("dimtofl", &DRW_Dimstyle::dimtofl)
    .property("dimsah", &DRW_Dimstyle::dimsah)
    .property("dimtix", &DRW_Dimstyle::dimtix)
    .property("dimsoxd", &DRW_Dimstyle::dimsoxd)
    .property("dimclrd", &DRW_Dimstyle::dimclrd)
    .property("dimclre", &DRW_Dimstyle::dimclre)
    .property("dimclrt", &DRW_Dimstyle::dimclrt)
    .property("dimadec", &DRW_Dimstyle::dimadec)
    .property("dimunit", &DRW_Dimstyle::dimunit)
    .property("dimdec", &DRW_Dimstyle::dimdec)
    .property("dimtdec", &DRW_Dimstyle::dimtdec)
    .property("dimaltu", &DRW_Dimstyle::dimaltu)
    .property("dimalttd", &DRW_Dimstyle::dimalttd)
    .property("dimaunit", &DRW_Dimstyle::dimaunit)
    .property("dimfrac", &DRW_Dimstyle::dimfrac)
    .property("dimlunit", &DRW_Dimstyle::dimlunit)
    .property("dimdsep", &DRW_Dimstyle::dimdsep)
    .property("dimtmove", &DRW_Dimstyle::dimtmove)
    .property("dimjust", &DRW_Dimstyle::dimjust)
    .property("dimsd1", &DRW_Dimstyle::dimsd1)
    .property("dimsd2", &DRW_Dimstyle::dimsd2)
    .property("dimtolj", &DRW_Dimstyle::dimtolj)
    .property("dimtzin", &DRW_Dimstyle::dimtzin)
    .property("dimaltz", &DRW_Dimstyle::dimaltz)
    .property("dimaltttz", &DRW_Dimstyle::dimaltttz)
    .property("dimfit", &DRW_Dimstyle::dimfit)
    .property("dimupt", &DRW_Dimstyle::dimupt)
    .property("dimatfit", &DRW_Dimstyle::dimatfit)
    .property("dimfxlon", &DRW_Dimstyle::dimfxlon)
    .property("dimtxsty", &DRW_Dimstyle::dimtxsty)
    .property("dimldrblk", &DRW_Dimstyle::dimldrblk)
    .property("dimlwd", &DRW_Dimstyle::dimlwd)
    .property("dimlwe", &DRW_Dimstyle::dimlwe);

  class_<DRW_LType, base<DRW_TableEntry>>("DRW_LType")
    .constructor<>()
    .function("reset", &DRW_LType::reset)
    .property("desc", &DRW_LType::desc)
    .property("size", &DRW_LType::size)
    .property("length", &DRW_LType::length)
    .property("path", &DRW_LType::path);

  class_<DRW_Layer, base<DRW_TableEntry>>("DRW_Layer")
    .constructor<>()
    .function("reset", &DRW_Layer::reset)
    .property("lineType", &DRW_Layer::lineType)
    .property("color", &DRW_Layer::color)
    .property("color24", &DRW_Layer::color24)
    .property("plotF", &DRW_Layer::plotF)
    .property("lWeight", &DRW_Layer::lWeight)
    .property("handlePlotS", &DRW_Layer::handlePlotS)
    .property("handleMaterialS", &DRW_Layer::handleMaterialS)
    .property("lTypeH", &DRW_Layer::lTypeH);

  class_<DRW_Block_Record, base<DRW_TableEntry>>("DRW_Block_Record")
    .constructor<>()
    .function("reset", &DRW_Block_Record::reset)
    .property("insUnits", &DRW_Block_Record::insUnits)
    .property("basePoint", &DRW_Block_Record::basePoint);

  class_<DRW_Vport, base<DRW_TableEntry>>("DRW_Vport")
    .constructor<>()
    .function("reset", &DRW_Vport::reset)
    .property("lowerLeft", &DRW_Vport::lowerLeft)
    .property("UpperRight", &DRW_Vport::UpperRight)
    .property("center", &DRW_Vport::center)
    .property("snapBase", &DRW_Vport::snapBase)
    .property("snapSpacing", &DRW_Vport::snapSpacing)
    .property("gridSpacing", &DRW_Vport::gridSpacing)
    .property("viewDir", &DRW_Vport::viewDir)
    .property("viewTarget", &DRW_Vport::viewTarget)
    .property("height", &DRW_Vport::height)
    .property("ratio", &DRW_Vport::ratio)
    .property("lensHeight", &DRW_Vport::lensHeight)
    .property("frontClip", &DRW_Vport::frontClip)
    .property("backClip", &DRW_Vport::backClip)
    .property("snapAngle", &DRW_Vport::snapAngle)
    .property("twistAngle", &DRW_Vport::twistAngle)
    .property("viewMode", &DRW_Vport::viewMode)
    .property("circleZoom", &DRW_Vport::circleZoom)
    .property("fastZoom", &DRW_Vport::fastZoom)
    .property("ucsIcon", &DRW_Vport::ucsIcon)
    .property("snap", &DRW_Vport::snap)
    .property("grid", &DRW_Vport::grid)
    .property("snapStyle", &DRW_Vport::snapStyle)
    .property("snapIsopair", &DRW_Vport::snapIsopair)
    .property("gridBehavior", &DRW_Vport::gridBehavior);

  class_<DRW_ImageDef, base<DRW_TableEntry>>("DRW_ImageDef")
    .constructor<>()
    .function("reset", &DRW_ImageDef::reset)
    .property("name", &DRW_ImageDef::name)
    .property("imgVersion", &DRW_ImageDef::imgVersion)
    .property("u", &DRW_ImageDef::u)
    .property("v", &DRW_ImageDef::v)
    .property("up", &DRW_ImageDef::up)
    .property("vp", &DRW_ImageDef::vp)
    .property("loaded", &DRW_ImageDef::loaded)
    .property("resolution", &DRW_ImageDef::resolution)
    .property("reactors", &DRW_ImageDef::reactors);

  class_<DRW_AppId, base<DRW_TableEntry>>("DRW_AppId")
    .constructor<>()
    .function("reset", &DRW_AppId::reset)
    .property("flags", &DRW_AppId::flags)
    .property("name", &DRW_AppId::name);
}

// Binding code
EMSCRIPTEN_BINDINGS(dxfRW) {
  class_<dxfRW>("dxfRW")
    .constructor<const char*>()
    ;
}
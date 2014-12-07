/**
 * \file GyotoObject.h
 * \brief Introspectbale objects 
 */

/*
    Copyright 2014 Thibaut Paumard

    This file is part of Gyoto.

    Gyoto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Gyoto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Gyoto.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __GyotoProperty_H_
#define __GyotoProperty_H_

#include "GyotoConfig.h"
#include <string>
#include <vector>

namespace Gyoto {
  class Object;
  class Property;
  namespace Metric { class Generic; }
  namespace Astrobj { class Generic; }
  namespace Spectrum { class Generic; }
  namespace Spectrometer { class Generic; }
  class Screen;
  template <class T> class SmartPointer;
}

#define GYOTO_PROPERTY_START(class) \
  Property const class::properties[] = {

/// Define a new Property of type Bool
/*
 * Declares a static variable named "name". name and namef should not
 * be quoted.
 *
 * \param[in] class name
 * \param[in] name name of property if true;
 * \param[in] namef name of property if false;
 * \param[in] fname name of functions for setting or getting the property
 * \param[in] ancestor pointer to next Property instance
 */
#define GYOTO_PROPERTY_BOOL(class, name, namef, fname)			\
  Gyoto::Property							\
  (#name,								\
   #namef,								\
   (Gyoto::Property::set_bool_t)&class :: fname,			\
   (Gyoto::Property::get_bool_t)&class :: fname),

/// Define a Property of type Double
#define GYOTO_PROPERTY_DOUBLE(class, name, fname)		\
  Gyoto::Property						\
  (#name,							\
   (Gyoto::Property::set_double_t)&class::fname,		\
   (Gyoto::Property::get_double_t)&class::fname),

/// Define a Property of type Long
#define GYOTO_PROPERTY_LONG(class, name, fname)		\
  Gyoto::Property					\
  (#name,						\
   (Gyoto::Property::set_long_t)&class::fname,		\
   (Gyoto::Property::get_long_t)&class::fname),

/// Define a Property of type Long
#define GYOTO_PROPERTY_UNSIGNED_LONG(class, name, fname)	\
  Gyoto::Property						\
  (#name,							\
   (Gyoto::Property::set_unsigned_long_t)&class::fname,		\
   (Gyoto::Property::get_unsigned_long_t)&class::fname),

#define GYOTO_PROPERTY_SIZE_T GYOTO_PROPERTY_UNSIGNED_LONG

/// Define a Property of type Double supporting unit
#define GYOTO_PROPERTY_DOUBLE_UNIT(class, name, fname) \
  Gyoto::Property						\
  (#name,							\
   (Gyoto::Property::set_double_t)&class::fname,		\
   (Gyoto::Property::get_double_t)&class::fname,		\
   (Gyoto::Property::set_double_unit_t)&class::fname,		\
   (Gyoto::Property::get_double_unit_t)&class::fname),

/// Define a Property of type Filename
#define GYOTO_PROPERTY_FILENAME(class, name, fname)		\
  Gyoto::Property						\
  (#name,							\
   (Gyoto::Property::set_string_t)&class::fname,		\
   (Gyoto::Property::get_string_t)&class::fname,		\
   true),

/// Define a Property of type String
#define GYOTO_PROPERTY_STRING(class, name, fname)			\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_string_t)&class::fname,			\
   (Gyoto::Property::get_string_t)&class::fname,			\
   false),

/// Define a Property of type vector<double>
#define GYOTO_PROPERTY_VECTOR_DOUBLE(class, name, fname)		\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_vector_double_t)&class::fname,			\
   (Gyoto::Property::get_vector_double_t)&class::fname),

/// Define a Property of type vector<double> with unit support
#define GYOTO_PROPERTY_VECTOR_DOUBLE_UNIT(class, name, fname)		\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_vector_double_t)&class::fname,			\
   (Gyoto::Property::get_vector_double_t)&class::fname,			\
   (Gyoto::Property::set_vector_double_unit_t)&class::fname,		\
   (Gyoto::Property::get_vector_double_unit_t)&class::fname),

/// Define a Property of type Gyoto::Metric::Generic
#define GYOTO_PROPERTY_METRIC(class, name, fname)			\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_metric_t)&class::fname,			\
   (Gyoto::Property::get_metric_t)&class::fname),

/// Define a Property of type Gyoto::Screen
#define GYOTO_PROPERTY_SCREEN(class, name, fname)			\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_screen_t)&class::fname,			\
   (Gyoto::Property::get_screen_t)&class::fname),

/// Define a Property of type Gyoto::Astrobj::Generic
#define GYOTO_PROPERTY_ASTROBJ(class, name, fname)			\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_astrobj_t)&class::fname,			\
   (Gyoto::Property::get_astrobj_t)&class::fname),

/// Define a Property of type Gyoto::Spectrum::Generic
#define GYOTO_PROPERTY_SPECTRUM(class, name, fname)			\
  Gyoto::Property							\
    (#name,								\
     (Gyoto::Property::set_spectrum_t)&class::fname,			\
     (Gyoto::Property::get_spectrum_t)&class::fname),

/// Define a Property of type Gyoto::Spectrometer::Generic
#define GYOTO_PROPERTY_SPECTROMETER(class, name, fname)			\
  Gyoto::Property							\
  (#name,								\
   (Gyoto::Property::set_spectrometer_t)&class::fname,			\
   (Gyoto::Property::get_spectrometer_t)&class::fname),

/// Define class::properties and class::getProperties() 
#define GYOTO_PROPERTY_END(class, next)				\
  Property(next)};							\
  Gyoto::Property const * class::getProperties() const {		\
    return class::properties;						\
  }

/**
 * \brief Property
 */
class Gyoto::Property
{
 private:

 public:
  enum type_e {double_t, long_t, unsigned_long_t, bool_t,
	       string_t, filename_t,
	       vector_double_t, metric_t, screen_t, astrobj_t, spectrum_t, spectrometer_t,
	       empty_t};
  std::string name;
  std::string name_false;
  int type;
  typedef void (Object::* set_double_t)(double val);
  typedef double (Object::* get_double_t)() const;
  typedef void (Object::* set_double_unit_t)(double val,
					     std::string const &unit);
  typedef double (Object::* get_double_unit_t)(std::string const &unit) const;
  typedef void (Object::* set_long_t)(long val);
  typedef long (Object::* get_long_t)() const;
  typedef void (Object::* set_unsigned_long_t)(unsigned long val);
  typedef unsigned long (Object::* get_unsigned_long_t)() const;
  typedef void (Object::* set_bool_t)(bool val);
  typedef bool (Object::* get_bool_t)() const;
  typedef void (Object::* set_string_t)(std::string const&);
  typedef std::string (Object::* get_string_t)() const;
  typedef void (Object::* set_fname_t)(std::string const&);
  typedef std::string (Object::* get_fname_t)() const;
  typedef void (Object::* set_vector_double_t)(std::vector<double> const&);
  typedef std::vector<double> (Object::* get_vector_double_t)() const;
  typedef void (Object::* set_vector_double_unit_t)(std::vector<double> const&, std::string const &);
  typedef std::vector<double> (Object::* get_vector_double_unit_t)(std::string const &) const;

  typedef void (Object::* set_metric_t)
    (Gyoto::SmartPointer<Gyoto::Metric::Generic>);
  typedef Gyoto::SmartPointer<Gyoto::Metric::Generic>
    (Object::* get_metric_t)() const;

  typedef void (Object::* set_screen_t)
    (Gyoto::SmartPointer<Gyoto::Screen>);
  typedef Gyoto::SmartPointer<Gyoto::Screen>
    (Object::* get_screen_t)() const;

  typedef void (Object::* set_astrobj_t)
    (Gyoto::SmartPointer<Gyoto::Astrobj::Generic>);
  typedef Gyoto::SmartPointer<Gyoto::Astrobj::Generic>
    (Object::* get_astrobj_t)() const;

  typedef void (Object::* set_spectrum_t)
    (Gyoto::SmartPointer<Gyoto::Spectrum::Generic>);
  typedef Gyoto::SmartPointer<Gyoto::Spectrum::Generic>
    (Object::* get_spectrum_t)() const;

  typedef void (Object::* set_spectrometer_t)
    (Gyoto::SmartPointer<Gyoto::Spectrometer::Generic>);
  typedef Gyoto::SmartPointer<Gyoto::Spectrometer::Generic>
    (Object::* get_spectrometer_t)() const;

  union setter_t {
    set_double_t set_double;
    set_long_t set_long;
    set_unsigned_long_t set_unsigned_long;
    set_bool_t set_bool;
    set_string_t set_string;
    set_vector_double_t set_vdouble;
    set_metric_t set_metric;
    set_screen_t set_screen;
    set_astrobj_t set_astrobj;
    set_spectrum_t set_spectrum;
    set_spectrometer_t set_spectrometer;
  };
  union getter_t {
    get_double_t get_double;
    get_long_t get_long;
    get_unsigned_long_t get_unsigned_long;
    get_bool_t get_bool;
    get_string_t get_string;
    get_vector_double_t get_vdouble;
    get_metric_t get_metric;
    get_screen_t get_screen;
    get_astrobj_t get_astrobj;
    get_spectrum_t get_spectrum;
    get_spectrometer_t get_spectrometer;
  };
  union setter_unit_t {
    set_double_unit_t set_double;
    set_vector_double_unit_t set_vdouble;
  };
  union getter_unit_t {
    get_double_unit_t get_double;
    get_vector_double_unit_t get_vdouble;
  };
  setter_t setter;
  getter_t getter;
  setter_unit_t setter_unit;
  getter_unit_t getter_unit;

  operator bool() const ;

  Property const * const  parent;
  
  Property(Property const * const ancestor);

  Property(std::string name,
	   set_long_t set_long,
	   get_long_t get_long);

  Property(std::string name,
	   set_unsigned_long_t set_unsigned_long,
	   get_unsigned_long_t get_unsigned_long);

  Property(std::string name,
	   set_double_t set_double,
	   get_double_t get_double);

  Property(std::string name,
	   set_double_t set_double,
	   get_double_t get_double,
	   set_double_unit_t set_double_unit,
	   get_double_unit_t get_double_unit);

  Property(std::string name,
	   std::string name_false,
	   set_bool_t set_bool,
	   get_bool_t get_bool);

  Property(std::string name,
	   set_string_t set_string,
	   get_string_t get_string,
	   bool is_filename);

  Property(std::string name,
	   set_vector_double_t set_vdouble,
	   get_vector_double_t get_vdouble);

  Property(std::string name,
	   set_vector_double_t set_vdouble,
	   get_vector_double_t get_vdouble,
	   set_vector_double_unit_t set_vdouble_unit,
	   get_vector_double_unit_t get_vdouble_unit);

  Property(std::string name,
	   set_metric_t set_metric,
	   get_metric_t get_metric);

  Property(std::string name,
	   set_screen_t set_screen,
	   get_screen_t get_screen);

  Property(std::string name,
	   set_astrobj_t set_astrobj,
	   get_astrobj_t get_astrobj);

  Property(std::string name,
	   set_spectrum_t set_spectrum,
	   get_spectrum_t get_spectrum);

  Property(std::string name,
	   set_spectrometer_t set_spectrometer,
	   get_spectrometer_t get_spectrometer);

  Property const * find(std::string name) const;

};

#endif
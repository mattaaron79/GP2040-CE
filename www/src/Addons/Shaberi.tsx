import { useTranslation } from 'react-i18next';
import { FormCheck, Row } from 'react-bootstrap';
import * as yup from 'yup';

import Section from '../Components/Section';
import FormControl from '../Components/FormControl';
import { AddonPropTypes } from '../Pages/AddonsConfigPage';

// ShaberiOptions (from config.proto + webconfig.cpp → frontend JSON keys):
// ShaberiAddonEnabled
// shaberiIsSenpai
// shaberiUartEnabled0
// shaberiUartEnabled1
// shaberiPinUartRx0
// shaberiPinUartTx0
// shaberiPinUartRx1
// shaberiPinUartTx1

export const shaberiScheme = {
	ShaberiAddonEnabled: yup
		.number()
		.label('Shaberi Enabled'),
	shaberiIsSenpai: yup
		.number()
		.label('Is Senpai')
		.validateRangeWhenValue('ShaberiAddonEnabled', 0, 1),
	shaberiUartEnabled0: yup
		.number()
		.label('UART0 Enabled')
		.validateRangeWhenValue('ShaberiAddonEnabled', 0, 1),
	shaberiPinUartRx0: yup
		.number()
		.label('UART0 RX Pin')
		.validatePinWhenValue('shaberiUartEnabled0'),
	shaberiPinUartTx0: yup
		.number()
		.label('UART0 TX Pin')
		.validatePinWhenValue('shaberiUartEnabled0'),
	shaberiUartEnabled1: yup
		.number()
		.label('UART1 Enabled')
		.validateRangeWhenValue('ShaberiAddonEnabled', 0, 1),
	shaberiPinUartRx1: yup
		.number()
		.label('UART1 RX Pin')
		.validatePinWhenValue('shaberiUartEnabled1'),
	shaberiPinUartTx1: yup
		.number()
		.label('UART1 TX Pin')
		.validatePinWhenValue('shaberiUartEnabled1'),
};

export const shaberiState = {
	ShaberiAddonEnabled: 0,
	shaberiIsSenpai: 0,
	shaberiUartEnabled0: 0,
	shaberiUartEnabled1: 0,
	shaberiPinUartRx0: -1,
	shaberiPinUartTx0: -1,
	shaberiPinUartRx1: -1,
	shaberiPinUartTx1: -1,
};

const Shaberi = ({ values, errors, handleChange, handleCheckbox }: AddonPropTypes) => {
	const { t } = useTranslation();
	return (
		<Section
			title={
				<a
					href="https://gp2040-ce.info/add-ons/shaberi"
					target="_blank"
					className="text-reset text-decoration-none"
				>
					{t('AddonsConfig:shaberi-header-text')}
				</a>
			}
		>
			<div id="ShaberiAddonOptions" hidden={!values.ShaberiAddonEnabled}>
				<Row className="mb-3">
					<FormCheck
						label={t('AddonsConfig:shaberi-is-senpai')}
						type="switch"
						id="shaberiIsSenpai"
						reverse
						checked={Boolean(values.shaberiIsSenpai)}
						onChange={() => handleCheckbox('shaberiIsSenpai')}
					/>
				</Row>

				<Row className="mb-3">
					<FormCheck
						label={t('AddonsConfig:shaberi-uart0-enabled')}
						type="switch"
						id="shaberiUartEnabled0"
						reverse
						checked={Boolean(values.shaberiUartEnabled0)}
						onChange={() => handleCheckbox('shaberiUartEnabled0')}
					/>
					{values.shaberiUartEnabled0 ? (
						<>
							<FormControl
								type="number"
								label={t('AddonsConfig:shaberi-uart0-rx-pin-label')}
								name="shaberiPinUartRx0"
								className="form-control-sm"
								groupClassName="col-sm-3 mb-3"
								value={values.shaberiPinUartRx0}
								error={errors.shaberiPinUartRx0}
								isInvalid={Boolean(errors.shaberiPinUartRx0)}
								onChange={handleChange}
								min={-1}
								max={29}
							/>
							<FormControl
								type="number"
								label={t('AddonsConfig:shaberi-uart0-tx-pin-label')}
								name="shaberiPinUartTx0"
								className="form-control-sm"
								groupClassName="col-sm-3 mb-3"
								value={values.shaberiPinUartTx0}
								error={errors.shaberiPinUartTx0}
								isInvalid={Boolean(errors.shaberiPinUartTx0)}
								onChange={handleChange}
								min={-1}
								max={29}
							/>
						</>
					) : null}
				</Row>

				<Row className="mb-3">
					<FormCheck
						label={t('AddonsConfig:shaberi-uart1-enabled')}
						type="switch"
						id="shaberiUartEnabled1"
						reverse
						checked={Boolean(values.shaberiUartEnabled1)}
						onChange={() => handleCheckbox('shaberiUartEnabled1')}
					/>
					{values.shaberiUartEnabled1 ? (
						<>
							<FormControl
								type="number"
								label={t('AddonsConfig:shaberi-uart1-rx-pin-label')}
								name="shaberiPinUartRx1"
								className="form-control-sm"
								groupClassName="col-sm-3 mb-3"
								value={values.shaberiPinUartRx1}
								error={errors.shaberiPinUartRx1}
								isInvalid={Boolean(errors.shaberiPinUartRx1)}
								onChange={handleChange}
								min={-1}
								max={29}
							/>
							<FormControl
								type="number"
								label={t('AddonsConfig:shaberi-uart1-tx-pin-label')}
								name="shaberiPinUartTx1"
								className="form-control-sm"
								groupClassName="col-sm-3 mb-3"
								value={values.shaberiPinUartTx1}
								error={errors.shaberiPinUartTx1}
								isInvalid={Boolean(errors.shaberiPinUartTx1)}
								onChange={handleChange}
								min={-1}
								max={29}
							/>
						</>
					) : null}
				</Row>
			</div>

			<FormCheck
				label={t('Common:switch-enabled')}
				type="switch"
				id="ShaberiAddonButton"
				reverse
				checked={Boolean(values.ShaberiAddonEnabled)}
				onChange={() => handleCheckbox('ShaberiAddonEnabled')}
			/>
		</Section>
	);
};

export default Shaberi;
